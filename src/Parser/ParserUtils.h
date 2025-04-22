#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <string>
#include <vector>
#include <sstream>

namespace ParserUtils {
// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& line, char delimiter);

// Function to trim whitespace from both ends of a string
std::string trim(const std::string& s);

// Function to check if a string is a number
bool is_number(const std::string& s);
}  // namespace ParserUtils

#endif  // PARSER_UTILS_H
