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

		T traverse(const BitStream &code) const
		{
			// How many nodes are on the current branch (including the current node)
			T branchNodes = (T)(m_tree.size() - 1) / 2;
			size_t treeIndex = 0;

			for (size_t i = 0; i < code.size(); ++i)
			{
				if (code[i] == 0)
				{
					branchNodes = m_tree[treeIndex];
					++treeIndex;
				}
				else
				{
					branchNodes -= m_tree[treeIndex] + 1;
					treeIndex += (size_t)m_tree[treeIndex] * 2 + 2;
				}

				if (treeIndex >= m_tree.size())
					return 0;
			}

			// If this isn't met, the code does not end on a leaf
			if (branchNodes == 0)
				return m_tree[treeIndex];
			return 0;
		}

		bool isLeaf(const BitStream &code) const
		{
			// How many nodes are on the current branch (including the current node)
			T branchNodes = (T)(m_tree.size() - 1) / 2;
			size_t treeIndex = 0;

			for (size_t i = 0; i < code.size(); ++i)
			{
				if (code[i] == 0)
				{
					branchNodes = m_tree[treeIndex];
					++treeIndex;
				}
				else
				{
					branchNodes -= m_tree[treeIndex] + 1;
					treeIndex += (size_t)m_tree[treeIndex] * 2 + 2;
				}

				if (treeIndex >= m_tree.size())
					return false;
			}

			return branchNodes == 0;
		}

	private:
		/**
			* @brief Huffman tree of nodes and leaves
			*
			* Nodes store the total number of nodes on their left branch, with the first value always being a node.
			* Each node has two children, though one may be an unused value.
			*/
		std::vector<T> m_tree;
	};
}