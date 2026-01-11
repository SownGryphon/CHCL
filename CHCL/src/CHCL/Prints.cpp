#include "Prints.h"

#include "Formatter.h"

void chcl::PrintBuffer(const Buffer &buffer)
{
	for (int i = 0; i < buffer.size(); ++i)
	{
		std::cout << Formatter::Format("{0:4x}", *(uint8_t*)buffer[i]);

		if (i % 32 == 31)
			std::cout << "\n";
		else
			std::cout << " ";
	}
}