#pragma once
namespace chcl
{
	class OctBool
	{
		unsigned char data;

		struct OctBoolEntry
		{
			OctBool &parent;
			const unsigned char index;

			OctBoolEntry(OctBool &parent, const unsigned char index);

			OctBoolEntry& operator=(const bool state);

			operator bool() const;
		};

	public:
		OctBool(unsigned char data);

		OctBoolEntry operator[](unsigned char index);

		operator bool() const;
	};
}