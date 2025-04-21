#ifndef DISTANCE_PARSER_H
#define DISTANCE_PARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "../DataStructures/Graph.h"


class DistanceParser  {
 public:
  template <typename T>
  static void parse_distances(const std::string& filename,
                              Graph<T>* driving_network,
                              Graph<T>* walking_network);

 private:
  static std::vector<std::string> split(const std::string& line, char delimiter);
  static std::string trim(const std::string& s);
  static bool is_number(const std::string& s);
  static double parse_distance_value(const std::string& value);
};

/** @brief function to split a line into tokens using a delimiter 
 *  @param line line to split
 *  @param delimiter character where we want to split the string
 *  @return vector<string> containing the substrings
 *  Complexity: O(n)
 */
std::vector<std::string> inline DistanceParser::split(const std::string& line,
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
std::string inline DistanceParser::trim(const std::string& s) {
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
bool inline DistanceParser::is_number(const std::string& s) {
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

/** @brief helper method to parse distance value after trimming the string. If value is X then return Infinite
 *  @param value string to parse distance from
 *  @return number in double form
 *  Complexity: O(1)
 */ 
double inline DistanceParser::parse_distance_value(const std::string& value) {
  std::string trimmed = trim(value);
  if (trimmed == "X") return INF;  // using the INF macro from Graph.h
  try {
    return std::stod(trimmed);
  } catch (const std::invalid_argument& e) {
    std::cerr << "Warning: Invalid distance value '" << value << "'"
              << std::endl;
    // return INF if the value is invalid just to make sure
    return INF;
  }
}
/** @paragraph 
 * @param filename files
 * @param driving_network driving graph
 * @param walking_network walking graph 
 *  This function parses the edges between locations of the files that cointain attributes about them.
 * It uses fstreams and if the file can't be opened or if its empty we return with 
 * a message reflecting that. Then while using getline to read each line of the file we call
 * the split function to split the line by the delimeter ',' and if there is a malformed line
 * we skip it. Then we set values of location1, location2, driving, and walking to the elements of the row
 * vector and we call is_number to check if driving and walking is a number string and if it isnt we skip to the next
 * line. We call then  We then add the id and its respective code to the id_code_map
 * and add the vertex with the code info to both the driving and walking graphs calling the addVertex function
 * @return void
 * Complexity: O(n)
*/
template <typename T>
void DistanceParser::parse_distances(const std::string& filename,
                                 Graph<T>* driving_network,
                                 Graph<T>* walking_network) {
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

    const std::string& location1 = row[0];
    const std::string& location2 = row[1];
    const std::string& driving = row[2];
    const std::string& walking = row[3];

    if (!is_number(driving) || !is_number(walking)) {
      std::cerr << "Warning: Skipping line with non-integer distances: " << line
                << std::endl;
      continue;
    }

    double driving_distance = parse_distance_value(driving);

    double walking_distance = parse_distance_value(walking);

    driving_network->addBidirectionalEdge(location1, location2,
                                          driving_distance);

    walking_network->addBidirectionalEdge(location1, location2,
                                          walking_distance);
  }

  file.close();
}
#endif
