#pragma once
namespace chcl
{
	class OctBool
	{
	private:
		unsigned char m_data;
	public:
		OctBool();
		OctBool(unsigned char data);

		inline bool operator[](unsigned char index) const { return get(index); }

		inline const bool get(unsigned char index) const { return m_data & (1 << index);	}
		const bool set(unsigned char index, const bool state);

		inline unsigned char& data() { return m_data; }
		inline const unsigned char& data() const { return m_data; }

		explicit operator bool() const;
	};
}