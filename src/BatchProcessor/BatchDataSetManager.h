#ifndef DATASET_MANAGER_H
#define DATASET_MANAGER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../DataParser/CSVParser.h"
#include "../DataParser/ParserUtils.h"
#include "../PalletPacking/DataStructures/Pallet.h"
#include "../PalletPacking/DataStructures/Truck.h"
#include "BatchUtils.h"

class BatchDataSetManager {
 public:
  BatchDataSetManager(std::vector<Pallet> pallets, Truck truck);

  int selectAndLoadDataset();

 private:
  CSVParser csv_data_parser;
  std::vector<Pallet> pallets;
  Truck truck;
};

#endif
