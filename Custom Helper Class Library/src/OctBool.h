#pragma once
namespace chcl
{
	class OctBool
	{
	public:
		OctBool();
		OctBool(unsigned char data);

		inline bool operator[](unsigned char index) const { return get(index); }

		inline const bool get(unsigned char index) const { return (data & (1 << index) >> index);	}
		const bool set(unsigned char index, const bool state);

		operator bool() const;
	private:
		unsigned char data;
	};
}