#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include "../RoutePlanning/location.h"
#include "../DataStructures/Graph.h"
class BatchInputManager {
public:
    BatchInputManager(Graph<std::string>* driving_network,
               Graph<std::string>* walking_network,std::unordered_map<std::string,
               std::string>* id_code_map, std::unordered_map<std::string, Location>* code_location_map);

    int getInputMode();
    void processInput(std::istream &input_stream, std::ostream &output_stream);

private:
    std::unordered_map<std::string, std::string>* id_code_map_;
    std::unordered_map<std::string, Location>* code_location_map_;
    Graph<std::string>* driving_network_;
    Graph<std::string>* walking_network_;

    void clearTerminal();
    bool ensureDirectory(const std::string &dir);
    static std::string trim(const std::string &str);
    void parseList(const std::string &value, std::vector<std::string> &list);
    static void parseSegments(const std::string &value,
                              std::vector<std::pair<std::string, std::string>> &segments);

    struct InputParameters {
        std::string mode;
        std::string source_id;
        std::string destination_id;
        std::vector<std::string> avoid_location_ids;
        std::vector<std::pair<std::string, std::string>> avoid_edge_ids;
        std::vector<std::string> include_location_id;
        double max_walk_time = 0.0;
        bool restricted_route_requested = false;
    };
};

#endif
