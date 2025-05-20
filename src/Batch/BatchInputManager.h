#ifndef BATCH_INPUT_MANAGER_H
#define BATCH_INPUT_MANAGER_H

#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Algorithms/APPROX/Greedy.h"
#include "../Algorithms/BF/BruteForce.h"
#include "../Algorithms/DP/DynamicProgramming.h"
#include "../Algorithms/ILP/ILPBridgePy.h"
#include "../Algorithms/ILP/IntegerLinearProgramming.h"
#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"
#include "../Parser/ParserUtils.h"
#include "../Utils.h"
#include "BatchState.h"
#include "BatchUtils.h"
class BatchInputManager {
 private:
  void generate_output_file(std::string& filename,
                            std::vector<Pallet>& used_pallets,
                            unsigned int& max_profit, std::string& message);
  std::vector<Pallet>& pallets;
  Truck& truck;
  unsigned int timeout_ms = 60000; // Default 1 minute

public:
  BatchInputManager(std::vector<Pallet>& pallets, Truck& truck);

  BatchState getInputMode();
  void processInput();
  void set_timeout_ms(unsigned int ms) { timeout_ms = ms; }
  unsigned int get_timeout_ms() const { return timeout_ms; }
  void select_timeout();
};

#endif  // BATCH_INPUT_MANAGER_H
