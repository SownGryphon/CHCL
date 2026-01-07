#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>

namespace chcl
{
	class Formatter
	{
	private:
		/**
		 * Regex for finding format fields
		 * Has 4 capture groups:
		 * 1. (always) field ID to match with argument
		 * 2. (optional) format width specifier
		 * 3. (optional) format precision specifier
		 * 4. (optional) format type specifier
		 */
		static constexpr char formatFieldRegex[] = R"(\{(\d+)(?::(\d*)\.(\d*)(.*?))?\})";
		inline static std::regex s_regex;
		inline static bool s_regexInit = false;

		// Struct to store information about a format field
		struct FormatField
		{
			std::smatch regexMatch; //< Field regex match
			int fieldIndex; //< Argument index
			std::string formattedValue = ""; //< Formatted value of the field
		};

	public:

		/**Format a string with arguments
		 * Format fields are in the form {n[:w.pf]}, including an optional format specifier
		 * n - the required parameter index
		 * w - an optional width
		 * p - an optional precision
		 * f - a set of optional flags to better control output
		 * 	Currently supported flags:
		 * 	- f - fixed point
		 * 	- e - scientific notation
		 */
		template <typename ...Ts> 
		static std::string Format(const std::string &formatString, Ts ...args)
		{
			if (!s_regexInit)
			try
			{
				s_regex = std::regex(formatFieldRegex);
				s_regexInit = true;
			}
			catch (std::exception e)
			{
				std::cout << "Formatter regex error: " << e.what() << "\n";
				return "";
			}

			std::sregex_iterator fieldsBegin(formatString.begin(), formatString.end(), s_regex);
			std::sregex_iterator fieldsEnd{};
			
			std::vector<FormatField> formatFields;
			std::vector<FormatField*> sortedFormatFields;
			
			size_t numFields = std::distance(fieldsBegin, fieldsEnd);
			formatFields.reserve(numFields);
			sortedFormatFields.reserve(numFields);

			for (std::sregex_iterator i = fieldsBegin; i != fieldsEnd; ++i)
			{
				std::smatch fieldMatch = *i;
				int index = std::stoi(fieldMatch[1].str());

				formatFields.push_back(FormatField{ fieldMatch, index, "" });
				sortedFormatFields.push_back(&formatFields.back());
			}

			std::sort(sortedFormatFields.begin(), sortedFormatFields.end(),
				[](FormatField *first, FormatField *second)
				{
					return first->fieldIndex < second->fieldIndex;
				}
			);

			int index = 0;
			auto fieldsIterBegin = sortedFormatFields.begin();
			auto fieldsIterEnd = sortedFormatFields.end();
			(... , FormatArg(index, fieldsIterBegin, fieldsIterEnd, args));

			std::ostringstream result;
			size_t unformattedBegin = 0;
			for (FormatField &field : formatFields)
			{
				size_t fieldBeginIndex = field.regexMatch.position();

				if (unformattedBegin < fieldBeginIndex)
				{
					result << formatString.substr(unformattedBegin, fieldBeginIndex - unformattedBegin);
				}

				result << field.formattedValue;

				unformattedBegin = fieldBeginIndex + field.regexMatch.length();
			}

			if (unformattedBegin < formatString.length())
				result << formatString.substr(unformattedBegin);

			return result.str();
		}
	
	private:
		
		template <typename T>
		static void FormatArg(int &index, std::vector<FormatField*>::iterator &fieldsIter, std::vector<FormatField*>::iterator &fieldsIterEnd, T arg)
		{
			while (fieldsIter != fieldsIterEnd && (*fieldsIter)->fieldIndex == index)
			{
				FormatField *field = *fieldsIter;

				std::ostringstream fieldFormatter;

				// Check for width parameter
				if (field->regexMatch.length(2))
				{
					int fieldWidth = std::stoi(field->regexMatch.str(2));
					fieldFormatter.width(fieldWidth);
				}

				// Check for precision parameter
				if (field->regexMatch.length(3))
				{
					int fieldPrecision = std::stoi(field->regexMatch.str(3));
					fieldFormatter.precision(fieldPrecision);
				}

				// Check for type flags
				if (field->regexMatch.length(4))
				{
					switch (*(field->regexMatch[4].first))
					{
					case 'f':
						fieldFormatter << std::fixed;
						break;
					case 'e':
						fieldFormatter << std::scientific;
						break;
					}
				}

				fieldFormatter << arg;

				field->formattedValue = fieldFormatter.str();
				
				++fieldsIter;
			}
			++index;
		}
	};
}