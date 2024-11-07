#include "JSON_Parser.h"

chcl::JSON_Stream& chcl::operator>>(JSON_Stream &stream, std::string &str)
{
	str.clear();

	bool escapedChar = false;
	std::string elemStr = stream.str();

	if (elemStr[0] != '\"') return stream;

	for (size_t i = 1; i < elemStr.length() - 1; ++i)
	{
		char currentChar = elemStr[i];

		if (escapedChar)
		{
			switch (currentChar)
			{
				case '\"':
					str.push_back('\"');
					break;
				case '\\':
					str.push_back('\\');
					break;
				case 'n':
					str.push_back('\n');
					break;
				case 'r':
					str.push_back('\r');
					break;
				case 't':
					str.push_back('\t');
					break;
				default:
					str.push_back(currentChar);
			}

			escapedChar = false;
			continue;
		}

		if (currentChar == '\\')
		{
			escapedChar = true;
			continue;
		}

		str.push_back(currentChar);
	}
	return stream;
}

chcl::JSON_Stream& chcl::operator>>(JSON_Stream &stream, bool &val)
{
	val = (stream.str() == "true");
	return stream;
}

chcl::JSON_Stream& chcl::operator<<(JSON_Stream &stream, const std::string &str)
{
	stream << '\"';
	for (char c : str)
	{
		switch (c)
		{
			case '\\':
			case '\"':
			case '\n':
			case '\r':
			case '\t':
				stream << '\\';
		}
		stream << c;
	}
	stream << '\"';
	return stream;
}

chcl::JSON_Stream& chcl::operator<<(JSON_Stream &stream, bool val)
{
	if (val)
		stream << "true";
	else
		stream << "false";
	return stream;
}

bool chcl::JSON_Parser::JumpWhitespace(const std::string &text, size_t &index)
{
	while (index < text.length())
	{
		switch (text[index])
		{
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				++index;
				break;
			default:
				return true;
		}
	}
	return false;
}

bool chcl::JSON_Parser::JumpSection(const std::string &text, size_t &index)
{
	if (text[index] != '{') return false;

	// Used as an emergency tracker in case of malformed file
	size_t lastIndex = index;

	++index;
	JumpWhitespace(text, index);

	while (index < text.length() && index != lastIndex)
	{
		lastIndex = index;

		// Skip label
		if (!JumpString(text, index)) break;
		// Skip ':' and jump to next element
		JumpWhitespace(text, index);
		if (text[index] == ':') ++index;
		else break;
		JumpWhitespace(text, index);
		// Skip next element
		if (!JumpElement(text, index)) break;
		JumpWhitespace(text, index);
		if (text[index] == ',') ++index;
		JumpWhitespace(text, index);

		if (text[index] == '}')
		{
			++index;
			return true;
		}
	}
	return false;
}

bool chcl::JSON_Parser::JumpArray(const std::string &text, size_t &index)
{
	if (text[index] != '[') return false;

	size_t lastIndex = index;

	++index;
	JumpWhitespace(text, ++index);

	while (index < text.length() && index != lastIndex)
	{
		lastIndex = index;

		// Skip the next element
		// If the element was deemed malformed, abandon and report the malform
		if (!JumpElement(text, index)) break;
		if (text[index] == ',') ++index;
		JumpWhitespace(text, index);

		if (text[index] == ']')
		{
			++index;
			return true;
		}
	}
	return false;
}

bool chcl::JSON_Parser::JumpString(const std::string &text, size_t &index)
{
	if (text[index] != '\"') return false;

	++index;

	while (index < text.length())
	{
		switch (text[index++])
		{
			case '\\':
				++index;
				break;
			case '\"':
				return true;
		}
	}
	return false;
}

bool chcl::JSON_Parser::JumpElement(const std::string &text, size_t &index)
{
	while (index < text.length())
	{
		switch (text[index])
		{
			case '{':
				return JumpSection(text, index);
			case '[':
				return JumpArray(text, index);
			case '\"':
				return JumpString(text, index);
			case ',':
			case '}':
			case ']':
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				return true;
			default:
				++index;
				break;
		}
	}
	return true;
}

chcl::JSON_Stream& chcl::operator>>(JSON_Stream &stream, JSON_Object &obj)
{
	obj.clear();

	size_t index = 1;
	std::string elemStr = stream.str();

	if (elemStr[0] != '{') return stream;

	JSON_Parser::JumpWhitespace(elemStr, index);
	while (index < elemStr.length())
	{
		size_t labelBegin = index;
		JSON_Parser::JumpElement(elemStr, index);
		std::string label;
		JSON_Stream labelStream{ elemStr.substr(labelBegin, index - labelBegin) };
		labelStream >> label;

		// Jump over ':' character and whitespace
		JSON_Parser::JumpWhitespace(elemStr, index);
		++index;
		JSON_Parser::JumpWhitespace(elemStr, index);

		size_t elemBegin = index;
		JSON_Parser::JumpElement(elemStr, index);
		obj.m_elements[label] = elemStr.substr(elemBegin, index - elemBegin);
		// Jump over ',' character and whitespace
		JSON_Parser::JumpWhitespace(elemStr, index);
		++index;
		JSON_Parser::JumpWhitespace(elemStr, index);

		// Return if we reached the end of the section
		if (elemStr[index] == '}')
			break;
	}

	return stream;
}

chcl::JSON_Stream& chcl::operator<<(JSON_Stream &stream, const JSON_Object &obj)
{
	stream.elemStream << "{\n";
	bool firstLine = true;
	for (auto const& [label, value] : obj.m_elements)
	{
		if (firstLine)
			firstLine = false;
		else
			stream.elemStream << ",\n";

		stream.elemStream << '\t';
		stream << label;
		stream.elemStream << ": ";

		std::string valueLine;
		std::istringstream valueStream{ value };
		while (std::getline(valueStream, valueLine))
		{
			stream.elemStream << valueLine;
			if (!valueStream.eof())
				stream.elemStream << "\n\t";
		}
	}
	stream.elemStream << "\n}";
	return stream;
}