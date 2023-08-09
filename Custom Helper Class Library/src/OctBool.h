#pragma once
namespace chcl
{
	class OctBool
	{
	public:
		OctBool();
		OctBool(unsigned char data);

		const bool operator[](unsigned char index) const;

		const bool get(unsigned char index) const;
		const bool set(unsigned char index, const bool state);

		operator bool() const;
	private:
		unsigned char data;
	};
}