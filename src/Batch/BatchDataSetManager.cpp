#include "BatchDataSetManager.h"

BatchDataSetManager::BatchDataSetManager(std::vector<Pallet> &pallets,
                                         Truck &truck, std::string &identifier)
    : pallets(pallets), truck(truck), current_identifier(identifier) {}

const std::vector<Pallet> &BatchDataSetManager::get_pallets() const {
  return pallets;
}

int BatchDataSetManager::select_and_load_dataset() {
  BatchUtils::clear_terminal();
  while (true) {
    if (!current_identifier.empty()) {
      std::cout << "Current dataset: " << current_identifier << "\n";
    }
    std::cout << "Files should be in the format:\n"
              << "Pallets_<X>.csv\n"
              << "TruckAndPallets_<X>.csv\n\n";
    std::string identifier;
    std::cout << "<X> (empty line to exit): ";
    std::getline(std::cin, identifier);

    identifier = ParserUtils::trim(identifier);

    if (identifier.empty()) {
      break;
    }

    if (load_dataset(identifier)) {
      std::string output_dir = Utils::get_absolute_dir("/output");
      Utils::ensure_directory(output_dir);
      if (!current_identifier.empty()) {
        BatchUtils::clear_terminal();
        std::cout << "Dataset updated to: " << identifier << "\n";
        std::cout << "Press Enter to continue...";
        std::string dummy;
        std::getline(std::cin, dummy);
      }
      current_identifier = identifier;
      break;
    } else {
      BatchUtils::clear_terminal();
      std::cerr << "ERROR: Could not open files." << std::endl;
      continue;
    }
  }

  return true;
}

void BatchDataSetManager::show_dataset() {
  BatchUtils::clear_terminal();
  if (!current_identifier.empty()) {
    std::cout << "Current dataset: " << current_identifier << "\n";
  }
  std::cout << "Pallets:\n";
  for (const Pallet &pallet : pallets) {
    std::cout << "id: " << pallet.get_id()
              << ", profit: " << pallet.get_profit()
              << ", weight: " << pallet.get_weight() << "\n";
  }

  std::cout << "\nTruck:\n";
  std::cout << "capacity: " << truck.get_capacity()
            << ", num_pallets: " << truck.get_num_pallets() << "\n";

  std::cout << "\nPress Enter to exit...";
  std::string input;
  std::getline(std::cin, input);
}

bool BatchDataSetManager::load_dataset(std::string identifier) {
  std::string pallets_filename = "/data/Pallets_" + identifier + ".csv";
  std::string pallets_file_str = Utils::get_absolute_dir(pallets_filename);
  std::string truck_filename = "/data/TruckAndPallets_" + identifier + ".csv";
  std::string truck_file_str = Utils::get_absolute_dir(truck_filename);

  std::ifstream pallets_file(pallets_file_str);
  std::ifstream truck_file(truck_file_str);

  if (!pallets_file.is_open() || !truck_file.is_open()) {
    return false;
  }

  csv_data_parser.parse(pallets_file_str, truck_file_str, pallets, truck);
  return true;
}
