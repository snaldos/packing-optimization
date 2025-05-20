#ifndef BATCH_DATASET_MANAGER_H
#define BATCH_DATASET_MANAGER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "../Parser/CSVParser.h"
#include "../Parser/ParserUtils.h"
#include "../Utils.h"
#include "BatchUtils.h"

class BatchDataSetManager {
 public:
  BatchDataSetManager(std::vector<Pallet>& pallets, Truck& truck);
  int select_and_load_dataset();
  void show_dataset();
  const std::vector<Pallet>& get_pallets() const;

 private:
  bool load_dataset(std::string identifier);
  CSVParser csv_data_parser;
  std::vector<Pallet>& pallets;
  Truck& truck;
  std::string current_identifier; // Tracks the current dataset identifier
};

#endif  // BATCH_DATASET_MANAGER_H
