#include"BatchProcessor.h"
#include"BatchDataSetManager.h"
#include"BatchInputManager.h"

BatchProcessor::BatchProcessor(Graph<std::string>* driving_network,
                               Graph<std::string>* walking_network,
                               std::unordered_map<std::string, std::string>* id_code_map,
                               std::unordered_map<std::string, Location>* code_location_map)
    : driving_network_(driving_network),
      walking_network_(walking_network),
      id_code_map_(id_code_map),
      code_location_map_(code_location_map) {}
/** @brief this function creates a BatchDataSetManager that calls the selectAndLoadDataset function
 *  and a BatchInputManager that calls the getInputMode function and if it's return value is 1 it 
 * returns the function
 * Complexity: Depends on called functions (dataset loading and getting the input)
*/
void BatchProcessor::start() {
    BatchDataSetManager data_manager=BatchDataSetManager(driving_network_,walking_network_,id_code_map_,code_location_map_);
    if(data_manager.selectAndLoadDataset()) return;
    BatchInputManager input_manager=BatchInputManager(driving_network_,walking_network_,id_code_map_,code_location_map_);
    if (input_manager.getInputMode()==1)return start();
}