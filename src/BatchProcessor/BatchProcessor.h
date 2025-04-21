// BatchProcessor.h
#ifndef BATCH_PROCESSOR_H
#define BATCH_PROCESSOR_H

#include <string>
#include <unordered_map>
#include "../DataStructures/Graph.h"
#include "../RoutePlanning/location.h"



class BatchProcessor {
public:
    BatchProcessor(Graph<std::string>* driving_network,
                   Graph<std::string>* walking_network,
                   std::unordered_map<std::string, std::string>* id_code_map,
                   std::unordered_map<std::string, Location>* code_location_map);

    void start();

private:
    Graph<std::string>* driving_network_;
    Graph<std::string>* walking_network_;
    std::unordered_map<std::string, std::string>* id_code_map_;
    std::unordered_map<std::string, Location>* code_location_map_;

    void clearTerminal();
};

#endif
