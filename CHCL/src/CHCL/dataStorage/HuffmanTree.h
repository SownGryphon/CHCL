#pragma once

#include <vector>

#include "chcl/dataStorage/BitStream.h"

namespace chcl
{
	template <typename T>
	class HuffmanTree
	{
	public:
		HuffmanTree() {}

		/**
		 * Generates a Deflate-style huffman tree from code lengths
		 * @param codeLengths Array of huffman code lengths, where the code length of the n-th element is the length of the huffman code of n
		 */
		HuffmanTree(const std::vector<T> &codeLengths)
		{
			T numCodes = 0;
			std::vector<T> codeLengthCount;
			for (T len : codeLengths)
			{
				if (codeLengthCount.size() < len + 1)
					codeLengthCount.resize(len + 1);

				++codeLengthCount[len];

				if (len != 0)
					++numCodes;
			}
			T maxLength = (T)codeLengthCount.size() - 1;

			size_t code = 0;
			std::vector<size_t> nextCode;
			nextCode.resize(maxLength + 1);
			for (uint8_t bits = 2; bits <= maxLength; ++bits)
			{
				code = (code + codeLengthCount[bits - 1]) << 1;
				nextCode[bits] = code;
			}


			// A minimum estimate is that every leaf except one will have an associated node
			m_tree.reserve(numCodes * 2 - 1);
			m_tree.push_back(0);
			T totalNodes = 0;

			for (T i = 0; i < codeLengths.size(); ++i)
			{
				T len = codeLengths[i];
				if (len == 0)
					continue;

				size_t treeIndex = 0;
				size_t branchNodes = totalNodes;
				std::vector<size_t> branchPath;
				branchPath.resize(len);
				for (T j = 0; j < len; ++j)
				{
					branchPath[j] = treeIndex;

					if (branchNodes == 0)
					{
						// Convert current leaf into node by giving it two child leaves
						m_tree.insert(m_tree.begin() + treeIndex + 1, 2, 0);

						++totalNodes;
						++branchNodes;

						for (T k = 0; k < j; ++k)
						{
							if (!(nextCode[len] & ((size_t)1 << (len - k - 1))))
								++m_tree[branchPath[k]];
						}
					}

					bool right = nextCode[len] & ((size_t)1 << (len - j - 1));

					if (right)
					{
						branchNodes -= m_tree[treeIndex];
						--branchNodes;

						size_t jumpDist = (size_t)m_tree[treeIndex] * 2 + 2;
						treeIndex += jumpDist;
					}
					else
					{
						branchNodes = m_tree[treeIndex];
						++treeIndex;
					}
				}

				++nextCode[len];
				m_tree[treeIndex] = i;
			}
		}

		/**
		 * Get the value associated with the given huffman code
		 * 
		 * @param code Huffman code of the value of interest
		 * 
		 * @returns Value for the huffman code.
		 * 	Returns 0 for codes that lead to non-leaf nodes.
		 */
		T traverse(const BitStream &code) const
		{
			size_t leafIndex = getLeafIndex(code);
			if (leafIndex == m_tree.size())
				return 0;
			return m_tree[leafIndex];
		}

		/**
		 * Checks if the given code leads to a leaf (value) node
		 * 
		 * @param code Bit stream containing the huffman code to check
		 * 
		 * @returns True if the value of the given code
		 */
		bool isLeaf(const BitStream &code) const
		{
			return getLeafIndex(code) != m_tree.size();
		}

	private:
		/**
		 * @brief Huffman tree of nodes, both internal and leaf nodes
		 *
		 * Internal nsodes store the total number of nodes on their left branch, with the first entry always being an internal node.
		 * Each internal node has two children, though one may be an unused value.
		 * Nodes are stored such that the parent node is always before its branches, and the left branch precedes the right branch
		 */
		std::vector<T> m_tree;

	private:
		/**
		 * Returns the position of the leaf node associated with the given code
		 * 
		 * @returns Index of node of interest.
		 * 	Will return one past the end of the tree for internal nodes or codes that do are malformed.
		 */
		size_t getLeafIndex(const BitStream &code)
		{
			// How many nodes are on the current branch (including the current node)
			T branchNodes = (T)(m_tree.size() - 1) / 2;
			size_t treeIndex = 0;

			for (size_t i = 0; i < code.size(); ++i)
			{
				if (code[i] == 0)	// Take left branch
				{
					branchNodes = m_tree[treeIndex];
					++treeIndex;
				}
				else	// Take right branch
				{
					branchNodes -= m_tree[treeIndex] + 1;
					treeIndex += (size_t)m_tree[treeIndex] * 2 + 2;
				}

				if (treeIndex >= m_tree.size())
					return m_tree.size();
			}

			// If this isn't met, the code does not end on a leaf
			if (branchNodes == 0)
				return treeIndex;
			return m_tree.size();
		}
	};
}