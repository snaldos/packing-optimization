#include "BatchDataSetManager.h"

BatchDataSetManager::BatchDataSetManager(std::vector<Pallet> pallets,
                                         Truck truck)
    : pallets(pallets), truck(truck) {};

int BatchDataSetManager::selectAndLoadDataset() {
  BatchUtils::clearTerminal();
  std::cout << "Write Data Set Identifier <X>:\n"
            << "(Empty line to exit)\n";
  std::string identifier;
  std::string pallets_filename;
  std::string truck_filename;

  while (true) {
    std::getline(std::cin, identifier);

    identifier = ParserUtils::trim(identifier);
    if (identifier.empty()) {
      std::cout << "Exiting..." << std::endl;
      return -1;
    }

    pallets_filename = "data/Pallets_" + identifier + ".csv";
    truck_filename = "data/TruckAndPallets_" + identifier + ".csv";

    std::ifstream pallets_file(pallets_filename);
    std::ifstream truck_file(truck_filename);

    if (!pallets_file.is_open() || !truck_file.is_open()) {
      std::cerr << "ERROR: Could not open files." << std::endl;
      continue;
    }

    csv_data_parser.parse(pallets_filename, truck_filename, pallets, truck);
    break;
  }

  std::cout << "Loaded dataset with identifier: " << identifier << std::endl;
  return 0;
}
