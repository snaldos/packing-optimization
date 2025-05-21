#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <string>
#include <vector>
#include <sstream>

/**
 * @namespace ParserUtils
 * @brief Utility functions for parsing and processing strings in CSV and user
 * input.
 */
namespace ParserUtils {
/**
 * @brief Splits a string by a delimiter character.
 * @param line Input string
 * @param delimiter Delimiter character
 * @return Vector of tokens
 */
std::vector<std::string> split(const std::string& line, char delimiter);

/**
 * @brief Trims whitespace from both ends of a string.
 * @param s Input string
 * @return Trimmed string
 */
std::string trim(const std::string& s);

/**
 * @brief Checks if a string represents a valid number.
 * @param s Input string
 * @return True if the string is a number, false otherwise
 */
bool is_number(const std::string& s);
}  // namespace ParserUtils

#endif  // PARSER_UTILS_H
