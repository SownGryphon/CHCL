#pragma once

#include <initializer_list>

#include "chcl/dataStorage/OctBool.h"

namespace chcl
{
	class OctBoolArray
	{
	private:
		unsigned int m_count, m_octBoolCount;
		OctBool* m_data;
	public:
		OctBoolArray();
		OctBoolArray(unsigned int size);
		OctBoolArray(std::initializer_list<bool> list);
		OctBoolArray(const OctBoolArray &other);
		~OctBoolArray();

		OctBoolArray& resize(unsigned int newCount);

		inline const bool operator[](unsigned int index) const { return get(index); }

		inline const bool get(unsigned int index) const { return m_data[index >> 3].get(index & 0b111); }
		inline const bool set(unsigned int index, const bool state) { return m_data[index >> 3].set(index & 0b111, state); }

		inline OctBool* data() { return m_data; }
		inline const OctBool* data() const { return m_data; }
		
		OctBoolArray& operator=(const OctBoolArray &other);
	};
}