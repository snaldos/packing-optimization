#include "ParserUtils.h"

namespace ParserUtils {
std::vector<std::string> split(const std::string& line, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream ss(line);
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string trim(const std::string& s) {
  size_t start = s.find_first_not_of(" \t\n\r");
  return (start == std::string::npos)
             ? ""
             : s.substr(start, s.find_last_not_of(" \t\n\r") + 1 - start);
}

bool is_number(const std::string& s) {
  std::string trimmed = trim(s);
  try {
    std::stod(trimmed);
    return true;
  } catch (const std::invalid_argument&) {
    return false;
  }
}
}  // namespace ParserUtils
