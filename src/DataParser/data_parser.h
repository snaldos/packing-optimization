#ifndef DATA_PARSER_H
#define DATA_PARSER_H

#include <unordered_map>
#include <string>
#include "../DataStructures/Graph.h"
#include "LocationParser.h"
#include "DistanceParser.h"
#include "../RoutePlanning/location.h"

class DataParser {
public:
  template <typename T>
  static void parse_data(const std::string& locations_filename,
                         const std::string& distances_filename,
                         std::unordered_map<std::string, std::string>& id_code_map,
                         std::unordered_map<std::string, Location>& code_location_map,
                         Graph<T>* driving_network, Graph<T>* walking_network);
};

/** @brief function that calls the parse_locations function to parse the location file and calls the 
 *  parse_distances function to parse the distance file.
 *  @param locations_filename locations file
 *  @param distances_filename distances file
 *  @param id_code_map map that links an id to its respective code
 *  @param code_location_map map that links a code to its respective location
 *  @param driving_network driving graph
 *  @param walking_network walking graph
 *  @return void
 *  Complexity: Depends on DistanceParser and LocationParser
*/
template <typename T>
void DataParser::parse_data(const std::string& locations_filename,
                            const std::string& distances_filename,
                            std::unordered_map<std::string, std::string>& id_code_map,
                            std::unordered_map<std::string, Location>& code_location_map,
                            Graph<T>* driving_network, Graph<T>* walking_network) {
  LocationParser::parse_locations(locations_filename, id_code_map, code_location_map,
                                  driving_network, walking_network);
  DistanceParser::parse_distances(distances_filename, driving_network, walking_network);
}
#endif
