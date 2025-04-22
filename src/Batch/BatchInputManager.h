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

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "../Parser/ParserUtils.h"
#include "BatchState.h"
#include "BatchUtils.h"
class BatchInputManager {
 public:
  BatchInputManager(std::vector<Pallet> pallets, Truck truck);

  BatchState getInputMode();
  void processInput(std::istream& input_stream, std::ostream& output_stream);
  void processFileInput();

 private:
  std::vector<Pallet> pallets;
  Truck truck;
};

#endif
