#include"RouteProcessor.h"
#include"algorithms.h"

RouteProcessor::RouteProcessor(Graph<std::string>* driving_network,
               Graph<std::string>* walking_network,
               std::unordered_map<std::string, Location>* code_location_map)
    :driving_network(driving_network),walking_network(walking_network), code_location_map(code_location_map) {
 }
/**
 * @brief 
 * Function to call the necessary algorithm functions  to solve the Driving problems that can be independent and restricted
 * If there is no best Alternative route we print a message saying there is none.
 * @return void
 * Complexity: Depends on functions called
 */
void RouteProcessor::processDrivingMode(
    const std::string &source_code, const std::string &destination_code,
    const std::vector<std::string> &avoid_location_codes,
    const std::vector<std::pair<std::string, std::string> > &avoid_edge_codes,
    const std::vector<std::string> &include_location_code,
    bool restricted_route_requested, std::ostream &output_stream) {
    Route best_route;
    Route alternative_route;
    Route restricted_route;

    if (!restricted_route_requested) {
        best_route = Algorithms::get_best_driving_route(
            driving_network, source_code, destination_code);
        alternative_route = Algorithms::get_best_alternative_driving_route(
            driving_network, best_route.get_location_codes(), source_code,
            destination_code);

        printRouteReport("BestDrivingRoute", best_route, output_stream);

        if (alternative_route.get_weight() == INF) {
            output_stream << "AlternativeDrivingRoute:none" << std::endl;
        } else {
            printRouteReport("AlternativeDrivingRoute", alternative_route,
                               output_stream);
        }
    }

    if (restricted_route_requested) {
        restricted_route = Algorithms::get_restricted_route(
            driving_network, source_code, destination_code, avoid_location_codes,
            avoid_edge_codes, include_location_code);

        printRouteReport("RestrictedDrivingRoute", restricted_route,
                           output_stream);
    }
}
/**
 * @brief 
 * Function to call the necessary algorithm functions to solve the Driving-Walking mode.
 * If there is no best case scenario set get_suggestions to true and call  the function again
 * and call the printAproximateSolutions function, if there is note print a message saying that.
 * @return void
 * Complexity: Depends on functions called
 */
void RouteProcessor::processDrivingWalkingMode(
        const std::string &source_code, const std::string &destination_code,
        double max_walk_time,
        const std::vector<std::string> &avoid_location_codes,
        const std::vector<std::pair<std::string, std::string> > &avoid_edge_codes,
        std::ostream &output_stream) {
        bool get_suggestions = false;
        size_t num_suggestions = 2;
        bool parking_exists = false;
        bool walking_route_within_time_exists = false;
        bool driving_route_exists = false;
        std::vector<std::pair<Route, Route> > suggestions;

        std::pair<Route, Route> best_driving_walking_route =
                Algorithms::get_best_driving_walking_route(
                    driving_network, walking_network, source_code, destination_code,
                    max_walk_time, avoid_location_codes, avoid_edge_codes,
                    *code_location_map, get_suggestions, num_suggestions,
                    parking_exists, walking_route_within_time_exists,
                    driving_route_exists, suggestions);

        if (best_driving_walking_route.first.get_weight() == INF ||
            best_driving_walking_route.second.get_weight() == INF) {
          // checks why the input didn't work
          printNoRouteMessage(max_walk_time, walking_route_within_time_exists,
                              parking_exists, driving_route_exists,
                              output_stream);

          // Try to get suggestions
          get_suggestions = true;
          suggestions.clear();
          parking_exists = walking_route_within_time_exists =
              driving_route_exists = false;  // Reset flags

          best_driving_walking_route =
              Algorithms::get_best_driving_walking_route(
                  driving_network, walking_network, source_code,
                  destination_code, max_walk_time, avoid_location_codes,
                  avoid_edge_codes, *code_location_map, get_suggestions,
                  num_suggestions, parking_exists,
                  walking_route_within_time_exists, driving_route_exists,
                  suggestions);

          if (!suggestions.empty()) {
            printApproximateSolutions(suggestions, output_stream);
          } else {
            output_stream << "No approximate solutions found." << std::endl;
          }
        } else {
          printBestDrivingWalkingRoute(best_driving_walking_route,
                                       output_stream);
        }
    }
  /** @brief function to print if there is no possible route and the various reasons why */
  void RouteProcessor::printNoRouteMessage(double max_walk_time, bool possible_walk_time, bool parking, bool driving_path,
                               std::ostream &output_stream) {
    output_stream << "DrivingRoute:" << std::endl;
    output_stream << "ParkingNode:" << std::endl;
    output_stream << "WalkingRoute:" << std::endl;
    output_stream << "TotalTime:" << std::endl;
    output_stream << "Message:";

    if (!parking) output_stream << "No parking location available." << std::endl;
    else if (!possible_walk_time)
        output_stream << "No possible route with max. walking time of "
                << max_walk_time << " minutes." << std::endl;
    else if (!driving_path) output_stream << "No driving path available." << std::endl;
}
/** @brief function to print the aproximate solutions to the problems
 * @param suggestions list of the possible dribing-walking solutions when there is no definitive best case
 * @param output_stream represents the source of where we print the output either a file or cout.
 * @return void
 * Complexity: O(n)
*/
void RouteProcessor::printApproximateSolutions(
        const std::vector<std::pair<Route, Route> > &suggestions,
        std::ostream &output_stream) {
    output_stream << "\nAPPROXIMATE SOLUTIONS:" << std::endl;
    for (size_t i = 0; i < suggestions.size(); ++i) {
        std::string parking_node = "none";
        if (!suggestions[i].second.get_location_codes().empty()) {
            parking_node = suggestions[i].second.get_location_codes().front();
        }

        std::string driving_route_str = "DrivingRoute" + std::to_string(i + 1);
        std::string walking_route_str = "WalkingRoute" + std::to_string(i + 1);

        output_stream << suggestions[i].first.generate_report(
            driving_route_str, *code_location_map);
        output_stream << "ParkingNode" << i + 1 << ":"
                << (*code_location_map)[parking_node].get_id()
                << std::endl;
        output_stream << suggestions[i].second.generate_report(
            walking_route_str, *code_location_map);
        output_stream << "TotalTime" << i + 1 << ":"
                << static_cast<int>(suggestions[i].first.get_weight() +
                                    suggestions[i].second.get_weight())
                << std::endl;
    }
}
/** @brief function to print the best driving-walking route
 * @param suggestions best driving-walking solution
 * @param output_stream represents the source of where we print the output either a file or cout.
 * @return void
 * Complexity: O(n)
*/
void RouteProcessor::printBestDrivingWalkingRoute(
        const std::pair<Route, Route> &best_driving_walking_route,
        std::ostream &output_stream) {
    std::string parking_node = "none";
    if (!best_driving_walking_route.second.get_location_codes().empty()) {
        parking_node =
                best_driving_walking_route.second.get_location_codes().front();
    }

    output_stream << best_driving_walking_route.first.generate_report(
        "DrivingRoute", *code_location_map);
    output_stream << "ParkingNode:"
            << (*code_location_map)[parking_node].get_id() << std::endl;
    output_stream << best_driving_walking_route.second.generate_report(
        "WalkingRoute", *code_location_map);
    output_stream << "TotalTime:"
            << best_driving_walking_route.first.get_weight() +
            best_driving_walking_route.second.get_weight()
            << std::endl;
}
/** @brief function to print the route report*/
void RouteProcessor::printRouteReport(const std::string& route_type, const Route& route,
                                        std::ostream& output_stream) {
    output_stream << route.generate_report(route_type, *code_location_map);
}