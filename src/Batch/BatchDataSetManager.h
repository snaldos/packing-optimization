#ifndef DATASET_MANAGER_H
#define DATASET_MANAGER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "../Parser/CSVParser.h"
#include "../Parser/ParserUtils.h"
#include "BatchUtils.h"

class BatchDataSetManager {
 public:
  BatchDataSetManager(std::vector<Pallet> pallets, Truck truck);

  int selectAndLoadDataset();
  void showDataset();

 private:
  // bool loadDataset();
  bool loadDataset(std::string identifier);
  CSVParser csv_data_parser;
  std::vector<Pallet> pallets;
  Truck truck;
};

#endif
