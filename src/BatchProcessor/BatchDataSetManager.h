#ifndef DATASET_MANAGER_H
#define DATASET_MANAGER_H

#include <string>
#include <unordered_map>
#include "../DataParser/data_parser.h"

class BatchDataSetManager {
public:
    BatchDataSetManager(Graph<std::string>* driving_network,
                   Graph<std::string>* walking_network,
                   std::unordered_map<std::string, std::string>* id_code_map,
                   std::unordered_map<std::string, Location>* code_location_map);

    int selectAndLoadDataset();

private:
    void clearTerminal();
    Graph<std::string>* driving_network_;
    Graph<std::string>* walking_network_;
    std::unordered_map<std::string, std::string>* id_code_map_;
    std::unordered_map<std::string, Location>* code_location_map_;
};

#endif
