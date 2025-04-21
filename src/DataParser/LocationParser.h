#ifndef LOCATION_PARSER_H
#define LOCATION_PARSER_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "../DataStructures/Graph.h"
#include "../RoutePlanning/location.h"

class LocationParser {
 public:
  template <typename T>
  static void parse_locations(const std::string& filename,
                              std::unordered_map<std::string, std::string>& id_code_map,
                              std::unordered_map<std::string, Location>& code_location_map,
                              Graph<T>* driving_network, Graph<T>* walking_network);

 private:
  static std::vector<std::string> split(const std::string& line, char delimiter);
  static std::string trim(const std::string& s);
  static bool is_number(const std::string& s);
};

/** @brief function to split a line into tokens using a delimiter 
 *  @param line line to split
 *  @param delimiter character where we want to split the string
 *  @return vector<string> containing the substrings
 *  Complexity: O(n)
 */
std::vector<std::string> inline LocationParser::split(const std::string& line,
                                           char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream ss(line);
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}
/** @brief function to remove the initial and final whitespace
 * @param s string to trim
 * @return trimmed string
 * Complexity: O(1)
*/
std::string inline LocationParser::trim(const std::string& s) {
  size_t start = s.find_first_not_of(" \t\n\r");
  return (start == std::string::npos)
             ? ""
             : s.substr(start, s.find_last_not_of(" \t\n\r") + 1 - start);
}

/** @brief helper method to check.If a string is a number if string is X it also return true.
 *  @param s string to check
 *  @return true if number or X else false
 *  Complexity: O(1)
*/
bool inline LocationParser::is_number(const std::string& s) {
  // trim whitespace first
  std::string trimmed = trim(s);

  // allow 'X' as a special value that means nope
  if (trimmed == "X") return true;

  // Try to parse as a number
  try {
    std::stod(trimmed);
    return true;
  } catch (const std::invalid_argument&) {
    return false;
  }
}


/** @paragraph 
 * @param filename represents the file or cin.
 * @param id_code_map map that links the code to its respective id
 * @param code_location_map map that links  the code to its respective location
 * @param driving_network driving graph
 * @param walking_network walking graph
 *  This function parses the locations of the files that cointain attributes about them.
 * It uses fstreams and if the file can't be opened or if its empty we return with 
 * a message reflecting that. Then while using getline to read each line of the file we call
 * the split function to split the line by the delimeter ',' and if there is a malformed line
 * we skip it. Then we set values of location, id, code, and parking tho the elements of the row
 * vector and we call is_number to check if id is a number string and if it isnt we skip to the next
 * line. We call then trim to delete the white space in parking and set has_parking to true if parking
 * is equal to '1' and false if it isnt. We then add the id and its respective code to the id_code_map
 * and add the vertex with the code info to both the driving and walking graphs calling the addVertex function
 * @return void
 * Complexity: O(n)
*/
template <typename T>
void LocationParser::parse_locations(
    const std::string& filename,
    std::unordered_map<std::string, std::string>& id_code_map,
    std::unordered_map<std::string, Location>& code_location_map,
    Graph<T>* driving_network, Graph<T>* walking_network) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::string line;
  // skip header line
  if (!std::getline(file, line)) {
    std::cerr << "Error: CSV file " << filename << " is empty." << std::endl;
    return;
  }

  while (std::getline(file, line)) {
    auto row = split(line, ',');
    if (row.size() != 4) {
      std::cerr << "Warning: Skipping malformed line: " << line << std::endl;
      continue;
    }

    const std::string& location = row[0];
    const std::string& id = row[1];
    const std::string& code = row[2];
    std::string parking = row[3];

    if (!is_number(id)) {
      std::cerr << "Warning: Skipping line with non-integer ID: " << line
                << std::endl;
      continue;
    }

    parking = trim(parking);  // Trim whitespace
    bool has_parking = (parking == "1");

    id_code_map[id] = code;
    code_location_map[code] = Location(location, id, code, has_parking);
    driving_network->addVertex(code);
    walking_network->addVertex(code);
  }

  file.close();
}
#endif
