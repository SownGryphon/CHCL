#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace chcl
{
	/**
	 * @brief Class for converting objects to/from JSON syntax.
	 * 
	 * To use with custom classes, overload operator<< and operator>> with JSON_Stream as lhs.
	 */
	struct JSON_Stream
	{
		std::stringstream elemStream;

		JSON_Stream() = default;
		JSON_Stream(const std::string &elem) : elemStream(elem) {}

		inline std::string str() const { return elemStream.str(); }

		template <typename T>
		friend JSON_Stream& operator>>(JSON_Stream &stream, T &elem);

		template <typename T>
		friend JSON_Stream& operator>>(JSON_Stream &stream, std::vector<T> &elem);

		friend JSON_Stream& operator>>(JSON_Stream &stream, std::string &str);
		friend JSON_Stream& operator>>(JSON_Stream &stream, bool &val);

		template <typename T>
		friend JSON_Stream& operator<<(JSON_Stream &stream, T elem);

		template <typename T>
		friend JSON_Stream& operator<<(JSON_Stream &stream, const std::vector<T> &elem);

		friend JSON_Stream& operator<<(JSON_Stream &stream, const std::string &elem);
		friend JSON_Stream& operator<<(JSON_Stream &stream, bool elem);
	};

	/**
	 * @brief Namespace containing read/write functions for JSON files.
	 */
	namespace JSON_Parser
	{
		bool JumpWhitespace(const std::string &text, size_t &index);
		bool JumpSection(const std::string &text, size_t &index);
		bool JumpArray(const std::string &text, size_t &index);
		bool JumpString(const std::string &text, size_t &index);
		bool JumpElement(const std::string &text, size_t &index);

		/**
		 * @brief Converts a string representing a JSON element to the appropriate object
		 * @tparam T Type to convert to
		 * @param elem String representation of
		 * @return Parsed object
		 */
		template <typename T>
		static T ParseElement(const std::string &elem)
		{
			size_t index = 0;
			JSON_Parser::JumpWhitespace(elem, index);
			size_t elemBegin = index;
			if (!JSON_Parser::JumpElement(elem, index)) return T();
			JSON_Stream elemStream{ elem.substr(elemBegin, index - elemBegin) };
			T result;
			elemStream >> result;
			return result;
		}

		/**
		 * @brief Reads and parses the contents of a .json file
		 * @tparam T
		 * @param filename
		 * @return
		 */
		template <typename T>
		static T ReadFile(const std::string &filename)
		{
			std::ifstream file{ filename };
			std::stringstream fileString;
			fileString << file.rdbuf();
			file.close();
			return JSON_Parser::ParseElement<T>(fileString.str());
		}

		/**
		 * @brief Saves the object to a JSON file
		 * @tparam T Object type to save
		 * @param filename Filename
		 * @param object Object to save
		 */
		template <typename T>
		static void SaveToFile(const std::string &filename, const T &object)
		{
			JSON_Stream formatStream;
			formatStream << object;
			std::ofstream fileStream{ filename };
			fileStream << formatStream.str();
			fileStream.close();
		}
	};

	/**
	 * @brief Class representing a JSON object with named fields.
	 */
	struct JSON_Object
	{
	public:
		/**
		 * @brief Reads the element with the given key from the JSON object
		 * @tparam T Type to read
		 * @param label Object label
		 * @return 
		 */
		template <typename T>
		T readElement(const std::string &label) { return JSON_Parser::ParseElement<T>(m_elements[label]); }

		/**
		 * @brief Formats and adds the element to the JSON object
		 * @tparam T Element type
		 * @param label Label to store the objet undex
		 * @param elem Element to store
		 */
		template <typename T>
		void writeElement(const std::string &label, const T &elem)
		{
			JSON_Stream outStream;
			outStream << elem;
			m_elements[label] = outStream.str();
		}

		inline void clear() { m_elements.clear(); }

		friend JSON_Stream& operator<<(JSON_Stream &stream, const JSON_Object &obj);
		friend JSON_Stream& operator>>(JSON_Stream &stream, JSON_Object &obj);

		/**
		 * @brief Contents of a single section.
		 * First element is the label, second element is the contents.
		 */
		std::unordered_map<std::string, std::string> m_elements;
	};

	template <typename T>
	JSON_Stream& operator>>(JSON_Stream &stream, T &elem)
	{
		stream.elemStream >> elem;
		return stream;
	}

	template <typename T>
	JSON_Stream& operator>>(JSON_Stream &stream, std::vector<T> &elem)
	{
		elem.clear();

		size_t index = 1;
		std::string elemStr = stream.str();

		if (elemStr[0] != '[') return stream;

		JSON_Parser::JumpWhitespace(elemStr, index);
		while (index < elemStr.length())
		{
			size_t elemStart = index;
			JSON_Parser::JumpElement(elemStr, index);
			JSON_Stream inStream{ elemStr.substr(elemStart, index - elemStart) };
			elem.resize(elem.size() + 1);
			inStream >> elem.back();
			JSON_Parser::JumpWhitespace(elemStr, index);
			++index;
			JSON_Parser::JumpWhitespace(elemStr, index);

			if (elemStr[index] == ']')
			{
				++index;
				break;
			}
		}
		return stream;
	}

	template <typename T>
	JSON_Stream& operator<<(JSON_Stream &stream, T elem)
	{
		stream.elemStream << elem;
		return stream;
	}

	template <typename T>
	JSON_Stream& operator<<(JSON_Stream &stream, const std::vector<T> &elem)
	{
		bool multiline = false;
		std::vector<JSON_Stream> formatStreams(elem.size());
		for (size_t i = 0; i < elem.size(); ++i)
		{
			formatStreams[i] << elem[i];

			std::string line;
			std::getline(formatStreams[i].elemStream, line);
			if (!formatStreams[i].elemStream.eof())
				multiline = true;
		}

		stream << '[';
		if (multiline)
		{
			stream << "\n";
			for (size_t i = 0; i < elem.size(); ++i)
			{
				if (i)
					stream << ",\n";
				std::string line;
				while (std::getline(formatStreams[i].elemStream, line))
				{
					stream << '\t' << line << '\n';
				}
			}
			stream << "\n";
		}
		else
		{
			stream << ' ';
			for (size_t i = 0; i < elem.size(); ++i)
			{
				if (i)
					stream << ", ";
				stream << elem[i];
			}
			stream << ' ';
		}
		stream << ']';

		return stream;
	}
}