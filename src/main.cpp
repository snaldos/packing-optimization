#include <string>
#include <unordered_map>

#include "DataStructures/Graph.h"
#include "RoutePlanning/location.h"
#include "BatchProcessor/BatchProcessor.h"


int main() {
    // Create graphs for driving and walking networks
    Graph<std::string> driving_network;
    Graph<std::string> walking_network;

    // Maps for ID to code and code to location
    std::unordered_map<std::string, std::string> id_code_map;
    std::unordered_map<std::string, Location> code_location_map;

    // Initialize batch processor
    BatchProcessor batch_processor(&driving_network, &walking_network,
                                   &id_code_map, &code_location_map);
    batch_processor.start();
    return 0;
}
