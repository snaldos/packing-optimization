#include "BatchDataSetManager.h"

BatchDataSetManager::BatchDataSetManager(Graph<std::string>* driving_network,
                   Graph<std::string>* walking_network,
                   std::unordered_map<std::string, std::string>* id_code_map,
                   std::unordered_map<std::string, Location>* code_location_map)
    : driving_network_(driving_network),
      walking_network_(walking_network),
      id_code_map_(id_code_map),
      code_location_map_(code_location_map) {}
/**  @brief helper method that clears the terminal
 *   @return void
 *   Complexity: O(1)
 */
void BatchDataSetManager::clearTerminal() {
    std::cout << "\033[2J\033[H" << std::flush;
    std::cout << "----- ROUTE PLANNING -----\n\n";
}
/** function that clears the terminal and then gives a message to the user to pick either "1: Large Data Set"
 * that if chosen sets distances_filename to "data/Distances.csv" and locations_filename to "data/Locations.csv"
 * and calls the parse_data function, "2: Test Data Set" that if chosen sets distances_filename to 
 * "data/TestDistances.csv" and locations_filename to "data/TestLocations.csv" and calls the parse_data funtion
 * and "3: exit" that if chosen terminates the function. if any other number or input is chosen it gives an error.
 * @return -1 if invalid input else 0
*/
int BatchDataSetManager::selectAndLoadDataset(){
clearTerminal();
std::cout << "Choose a Data Set:\n"
        << "1: Large Data Set" << std::endl
        << "2: Test Data Set\n" << std::endl
        << "3: exit" << std::endl;
std::string distances_filename;
std::string locations_filename;
while (true) {
    int datasetChoice;
    std::string input_dataset;
    std::getline(std::cin, input_dataset);

    try {
        datasetChoice = std::stoi(input_dataset);
    } catch (const std::invalid_argument &e) {
        std::cerr << "ERROR: Input MUST be a number." << std::endl;
        continue;
    }

    switch (datasetChoice) {
        case 1:
            distances_filename = "data/Distances.csv";
        locations_filename = "data/Locations.csv";
        // Parse data
        DataParser::parse_data(locations_filename, distances_filename, *id_code_map_,
                               *code_location_map_, driving_network_, walking_network_);
        return 0;
        case 2:
            distances_filename = "data/TestDistances.csv";
        locations_filename = "data/TestLocations.csv";

        // Parse data
        DataParser::parse_data(locations_filename, distances_filename, *id_code_map_,
                               *code_location_map_, driving_network_, walking_network_);
        return 0;
        case 3:
            return -1;
        default:
            std::cerr << "ERROR: Invalid Dataset Choice" << std::endl;
        break;
        }
    }
}