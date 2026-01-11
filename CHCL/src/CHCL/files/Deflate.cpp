#include "Deflate.h"

#include <iostream>

#include "CHCL/dataStorage/BitStreamView.h"
#include "CHCL/dataStorage/HuffmanTree.h"

#include "CHCL/misc/Profiler.h"

chcl::HuffmanTree<uint16_t> g_fixedLenHuffmanTree;
chcl::HuffmanTree<uint16_t> g_fixedDistHuffmanTree;

// Leave lenTree and distTree blank for fixed tree decompression
void HuffmanDecompress(chcl::BitStreamView &dataView, chcl::Buffer &output, const chcl::HuffmanTree<uint16_t> *lenTree = nullptr, const chcl::HuffmanTree<uint16_t> *distTree = nullptr);

chcl::Buffer chcl::DeflateDecomp(const void *compressedData, size_t predictedSize)
{
	ProfileScope(deflate)

	if (g_fixedLenHuffmanTree.getLeafCount() == 0)
	{
		ProfileScope(fixed_tree_gen)
		std::vector<uint16_t> lenCodeLengths;

		for (int i = 0; i <= 287; ++i)
		{
			if (i <= 143) lenCodeLengths.push_back(8);
			else if (i <= 255) lenCodeLengths.push_back(9);
			else if (i <= 279) lenCodeLengths.push_back(7);
			else lenCodeLengths.push_back(8);
		}

		g_fixedLenHuffmanTree = chcl::HuffmanTree<uint16_t>(lenCodeLengths);

		std::vector<uint16_t> distCodeLengths(32, 5);

		g_fixedDistHuffmanTree = chcl::HuffmanTree<uint16_t>(distCodeLengths);
	}

	Buffer decompressedData;
	if (predictedSize)
		decompressedData.reserve(predictedSize);
	
	BitStreamView dataView((const uint8_t*)compressedData);

	bool isFinalBlock = false;

	while (!isFinalBlock)
	{
		isFinalBlock = dataView.readBit();

		uint8_t blockCompressionType = dataView.readBits<uint8_t>(2);

		switch (blockCompressionType)
		{
			case 0x0: // Type 00, no compression
			{
				ProfileScope(no_compress)
				dataView.skipTrailingBits();

				uint16_t len = dataView.readBits<uint16_t>(16);
				uint16_t nlen = dataView.readBits<uint16_t>(16);

				decompressedData.append(dataView.readPos(), len);
				dataView.jump(len * 8);
				break;
			}
			case 0x1: // Type 01, fixed Huffman codes
			{
				ProfileScope(fixed_compress)
				HuffmanDecompress(dataView, decompressedData);
				break;
			}
			case 0x2: // Type 10, dynamic Huffman codes
			{
				ProfileScope(dynamic_compress)

				ProfileBegin(dynamic_tree_gen)
				ProfileBegin(code_tree_gen)
				uint8_t hlit = dataView.readBits<uint8_t>(5);
				uint8_t hdist = dataView.readBits<uint8_t>(5);
				uint8_t hclen = dataView.readBits<uint8_t>(4);

				constexpr size_t codeOrder[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
				// Initialize with 19 0's
				std::vector<uint8_t> codeLenTreeCodeLengths(19, 0);

				for (uint8_t i = 0; i < hclen + 4; i++)
					codeLenTreeCodeLengths[codeOrder[i]] = dataView.readBits<uint8_t>(3);

				chcl::HuffmanTree<uint8_t> codeLenTree(codeLenTreeCodeLengths);

				ProfileEnd(code_tree_gen)

				// Entire lambda to extract tree code lengths
				auto constructTreeLengths = [&codeLenTree, &dataView](size_t numLengths) -> std::vector<uint16_t>
				{
					std::vector<uint16_t> codeLengths;
					codeLengths.reserve(numLengths);
					while (codeLengths.size() < numLengths)
					{
						BitStream lenCodeCodeLenCode;
						while (!codeLenTree.isLeaf(lenCodeCodeLenCode))
							lenCodeCodeLenCode.pushBit(dataView.readBit());

						uint8_t lenCodeCode = codeLenTree.traverse(lenCodeCodeLenCode);

						if (lenCodeCode <= 15) codeLengths.push_back(lenCodeCode);
						else
						{
							uint8_t repeatLen = 0;
							switch (lenCodeCode)
							{
								case 16: repeatLen = dataView.readBits(2) + 3; break;
								case 17: repeatLen = dataView.readBits(3) + 3; break;
								case 18: repeatLen = dataView.readBits(7) + 11; break;
							}

							uint8_t repeatValue = 0;
							if (lenCodeCode == 16)
								repeatValue = codeLengths.back();
							
							for (int i = 0; i < repeatLen; i++)
								codeLengths.push_back(repeatValue);
						}
					}

					return codeLengths;
				};


				chcl::HuffmanTree<uint16_t> lenCodeTree(constructTreeLengths(hlit + 257));
				chcl::HuffmanTree<uint16_t> distCodeTree(constructTreeLengths(hdist + 1));

				ProfileEnd(dynamic_tree_gen);

				HuffmanDecompress(dataView, decompressedData, &lenCodeTree, &distCodeTree);

				break;
			}
		}
	}

	return decompressedData;
}

void HuffmanDecompress(chcl::BitStreamView &dataView, chcl::Buffer &output, const chcl::HuffmanTree<uint16_t> *lenTree, const chcl::HuffmanTree<uint16_t> *distTree)
{
	// ProfileScope(huffman_decompress)

	bool isFinalByte = false;

	if (lenTree == nullptr)
		lenTree = &g_fixedLenHuffmanTree;

	if (distTree == nullptr)
		distTree = &g_fixedDistHuffmanTree;

	while (!isFinalByte)
	{
		chcl::BitStream lenCodeCode;
		while (!lenTree->isLeaf(lenCodeCode))
			lenCodeCode.pushBit(dataView.readBit());

		uint16_t lengthCode = lenTree->traverse(lenCodeCode);

		if (lengthCode <= 255)	// length code is literal value
			output.append((uint8_t)lengthCode);
		else if (lengthCode == 256) // length code is end of block
			isFinalByte = true;
		else // length code is an actual code
		{
			uint16_t length = 0;

			if (lengthCode <= 264) length = lengthCode - 254;
			else if (lengthCode == 285) length = 258;
			else // lengthCode >= 265
			{
				uint8_t lenExtraBits = (lengthCode - 261) / 4;

				length = (4 << lenExtraBits) + 3 + ((lengthCode - 261 - lenExtraBits * 4) << lenExtraBits);
				
				length += dataView.readBits<uint16_t>(lenExtraBits);
			}
			

			uint8_t distCode = 0;
			if (distTree == nullptr)
				distCode = dataView.readBits<uint8_t>(5);
			else
			{
				chcl::BitStream distCodeCode;

				while (!distTree->isLeaf(distCodeCode))
				{
					distCodeCode.pushBit(dataView.readBit());
				}

				distCode = distTree->traverse(distCodeCode);
			}

			uint16_t dist = 0;
			if (distCode <= 3) dist = distCode + 1;
			else
			{
				uint8_t distExtraBits = (distCode - 2) / 2;

				dist = (2 << distExtraBits) + 1 + ((distCode - 2 - distExtraBits * 2) << distExtraBits);

				dist += dataView.readBits<uint16_t>(distExtraBits);
			}

			output.reserve(output.size() + length);

			const void *copyDataBegin = (uint8_t*)output.end() - dist;
			size_t copied = 0;
			while (length > 0)
			{
				size_t lenToCopy = std::min<size_t>(length, dist + copied);
				output.append(copyDataBegin, lenToCopy);
				copied += lenToCopy;
				length -= lenToCopy;
			}
		}
	}
}