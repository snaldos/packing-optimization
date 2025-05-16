#ifndef INTEGER_LINEAR_PROGRAMMING_H
#define INTEGER_LINEAR_PROGRAMMING_H

#include <chrono>
#include <ortools/linear_solver/linear_solver.h>
#include <string>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"

class IntegerLinearProgramming {
 public:
  unsigned int solve_ilp_cpp(const std::vector<Pallet>& pallets,
                             const Truck& truck,
                             std::vector<Pallet>& used_pallets,
                             std::string& message);
};

#endif  // INTEGER_LINEAR_PROGRAMMING_H
