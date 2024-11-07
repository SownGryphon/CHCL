#include "BinaryFile.h"

chcl::BinaryFile::BinaryFile(const std::string &filename, Endianness defaultEndian) :
	std::ifstream(filename, std::ifstream::in | std::istream::binary),
	m_defaultEndian(defaultEndian)
{}