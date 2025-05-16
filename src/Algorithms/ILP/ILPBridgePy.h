#ifndef ILPBRIDGE_H
#define ILPBRIDGE_H

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"
#include "../../Utils.h"

/*

  - This task will require some critical thinking and analysis skills. You
  should develop and analyze your own ILP approach to the 0/1KP.
  - You should mathematically formulate the 0/1KP properly as an ILP.
  - As an alternative to ILP you are free to pursue other algorithmic approaches
  such as Genetic Algorithms or a Hybrid Algorithmic approach specifically
  suited to selected input datasets.
  - Critically discuss your justification for the algorithms implemented.

*/

class ILPBridgePy {
 public:
  unsigned int solve_ilp_py(const std::vector<Pallet>& pallets,
                            const Truck& truck,
                            std::vector<Pallet>& used_pallets,
                            std::string& message);
};

#endif  // ILPBRIDGE_H
