#pragma once

/*
Written by Evgeny Solomin
Last edited 28/03/2024
*/

#include <functional>
#include <vector>

#define HEAP_TEMPL template <typename T, bool(*comp)(const T&, const T&)>

namespace chcl
{
	/**
	 * @brief
	 * @tparam T Type to store in binary heap
	 * @tparam comp Comparison function. If comp(a, b) returns true, a will be placed above b.
	 */
	HEAP_TEMPL
	class BinaryHeap
	{
	public:
		/**
		 * @brief Adds an item to the binary heap and sorts it into place
		 * @param item Item to add
		 */
		void add(const T &item);

		/**
		 * @brief Gets a const reference to the top item of the heap
		 * @return A const reference to the top item
		 */
		inline const T& getTop() const { return m_elements[0]; }

		/**
		 * @brief Gets the top item in the heap and removes it
		 * @return Item at the top of the heap
		 */
		T pop();
	private:
		inline void swap(size_t index1, size_t index2) { std::swap(m_elements[index1], m_elements[index2]); }

		void sortUp(size_t index);
		void sortDown(size_t index);

		std::vector<T> m_elements;
	};
};

HEAP_TEMPL
void chcl::BinaryHeap<T, comp>::add(const T &item)
{
	m_elements.push_back(item);
	sortUp(m_elements.size() - 1);
}

HEAP_TEMPL
T chcl::BinaryHeap<T, comp>::pop()
{
	swap(0, m_elements.size() - 1);
	T result = m_elements.back();
	m_elements.pop_back();
	sortDown(0);
	return result;
}

HEAP_TEMPL
void chcl::BinaryHeap<T, comp>::sortUp(size_t index)
{
	if (!index)
		return;

	size_t upIndex = (index - 1) / 2;
	if (comp(m_elements[index], m_elements[upIndex]))
	{
		swap(index, upIndex);
		sortUp(upIndex);
	}
}

HEAP_TEMPL
void chcl::BinaryHeap<T, comp>::sortDown(size_t index)
{
	size_t downIndex1 = index * 2 + 1, downIndex2 = downIndex1 + 1;

	// Trying to sort element with no child elements
	if (downIndex1 >= m_elements.size())
		return;

	if (downIndex2 < m_elements.size()	// Make sure that index 2 is valid
		&& comp(m_elements[downIndex2], m_elements[downIndex1])) // Check that item at index 2 is ranked higher than the one at index 1
	{
		if (comp(m_elements[downIndex2], m_elements[index]))	// Do comparison against item at current index
		{
			swap(index, downIndex2);
			sortDown(downIndex2);
		}
		// Exit early regardless of whether we actually swapped
		// Since index 2 is greater than index 1, no reason to try index 1 as well
		return;
	}

	if (comp(m_elements[downIndex1], m_elements[index]))
	{
		swap(index, downIndex1);
		sortDown(downIndex1);
	}
}

#undef HEAP_TEMPL