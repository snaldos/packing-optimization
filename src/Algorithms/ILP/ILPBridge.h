#ifndef ILPBRIDGE_H
#define ILPBRIDGE_H

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"
#include "../../Utils.h"

class ILPBridge {
 public:
  unsigned int solve_with_ilp(const std::vector<Pallet>& pallets,
                              const Truck& truck,
                              std::vector<Pallet>& used_pallets,
                              std::string& message);
};

#endif  // ILPBRIDGE_H
