#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../DataParser/ParserUtils.h"
#include "../PalletPacking/DataStructures/Pallet.h"
#include "../PalletPacking/DataStructures/Truck.h"
#include "BatchUtils.h"
class BatchInputManager {
 public:
  BatchInputManager(std::vector<Pallet> pallets, Truck truck);

  int getInputMode();
  void processInput(std::istream& input_stream, std::ostream& output_stream);

 private:
  std::vector<Pallet> pallets;
  Truck truck;
};

#endif
