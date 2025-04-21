// RouteProcessor.h
#ifndef ROUTE_PROCESSOR_H
#define ROUTE_PROCESSOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../DataStructures/Graph.h"
#include "../RoutePlanning/location.h"
#include "../RoutePlanning/route.h"

class RouteProcessor {
public:
    RouteProcessor(Graph<std::string>* driving_network,
                   Graph<std::string>* walking_network,
                   std::unordered_map<std::string, Location>* code_location_map);

    void processDrivingMode(const std::string &source_code,
                            const std::string &destination_code,
                            const std::vector<std::string> &avoid_location_codes,
                            const std::vector<std::pair<std::string, std::string>> &avoid_edge_codes,
                            const std::vector<std::string> &include_location_code,
                            bool restricted_route_requested,
                            std::ostream &output_stream);

    void processDrivingWalkingMode(const std::string &source_code,
                                   const std::string &destination_code,
                                   double max_walk_time,
                                   const std::vector<std::string> &avoid_location_codes,
                                   const std::vector<std::pair<std::string, std::string>> &avoid_edge_codes,
                                   std::ostream &output_stream);

private:
    Graph<std::string>* driving_network;
    Graph<std::string>* walking_network;
    std::unordered_map<std::string, Location>* code_location_map;

    // Helper methods for reporting routes
    void printRouteReport(const std::string &route_type, const Route &route, std::ostream &output_stream);
    void printNoRouteMessage(double max_walk_time, bool possible_walk_time,
                             bool parking, bool driving_path, std::ostream &output_stream);
    void printApproximateSolutions(const std::vector<std::pair<Route, Route>> &suggestions, std::ostream &output_stream);
    void printBestDrivingWalkingRoute(const std::pair<Route, Route> &best_route, std::ostream &output_stream);
};

#endif
