#include "BatchDataSetManager.h"

BatchDataSetManager::BatchDataSetManager(std::vector<Pallet> pallets,
                                         Truck truck)
    : pallets(pallets), truck(truck) {};

int BatchDataSetManager::selectAndLoadDataset() {
  BatchUtils::clearTerminal();
  while (true) {
    std::cout << "Files should be in the format:\n"
              << "Pallets_<X>.csv\n"
              << "TruckAndPallets_<X>.csv\n";
    std::string identifier;
    std::cout << "<X>: ";
    std::getline(std::cin, identifier);

    identifier = ParserUtils::trim(identifier);

    if (loadDataset(identifier)) {
      // std::cout << "Dataset loaded successfully.\n";
      break;
    } else {
      BatchUtils::clearTerminal();
      std::cerr << "ERROR: Could not open files." << std::endl;
      continue;
    }
  }

  return true;
}

void BatchDataSetManager::showDataset() {
  BatchUtils::clearTerminal();
  std::cout << "Pallets:\n";
  for (const Pallet& pallet : pallets) {
    std::cout << "id: " << pallet.get_id()
              << ", profit: " << pallet.get_profit()
              << ", weight: " << pallet.get_weight() << "\n";
  }

  std::cout << "Truck:\n";
  std::cout << "capacity: " << truck.get_capacity()
            << ", num_pallets: " << truck.get_num_pallets() << "\n";

  std::cout << "Press Enter to exit..." << std::endl;
  while (true) {
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
      break;
    }
  }
}

bool BatchDataSetManager::loadDataset(std::string identifier) {
  std::string pallets_filename = "data/Pallets_" + identifier + ".csv";
  std::string truck_filename = "data/TruckAndPallets_" + identifier + ".csv";

  std::ifstream pallets_file(pallets_filename);
  std::ifstream truck_file(truck_filename);

  if (!pallets_file.is_open() || !truck_file.is_open()) {
    return false;
  }

  csv_data_parser.parse(pallets_filename, truck_filename, pallets, truck);
  return true;
}
