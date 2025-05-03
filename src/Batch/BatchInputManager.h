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

#include "../Algorithms/BruteForce.h"
#include "../Algorithms/DynamicProgramming.h"
#include "../Algorithms/Greedy.h"
#include "../Algorithms/ILPBridge.h"
#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "../Parser/ParserUtils.h"
#include "BatchState.h"
#include "BatchUtils.h"
class BatchInputManager {
 private:
  void generate_output_file(std::string& filename,
                            std::vector<Pallet>& used_pallets,
                            unsigned int& max_profit, std::string& message);
  std::vector<Pallet>& pallets;
  Truck& truck;

 public:
  BatchInputManager(std::vector<Pallet>& pallets, Truck& truck);

  BatchState getInputMode();
  void processInput();
};

#endif
