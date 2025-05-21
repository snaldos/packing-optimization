#ifndef INTEGER_LINEAR_PROGRAMMING_H
#define INTEGER_LINEAR_PROGRAMMING_H

#include <chrono>
#include <ortools/linear_solver/linear_solver.h>
#include <string>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"

/**
 * @class IntegerLinearProgramming
 * @brief Solves the 0/1 Knapsack Problem using Integer Linear Programming
 * (ILP).
 *
 * Formulates the problem as an ILP and solves it using an external solver
 * (e.g., OR-Tools CBC).
 *
 * Time complexity: Depends on the ILP solver; exponential in the worst case,
 * but often efficient for moderate n. Space complexity: Depends on the solver's
 * internal representation (typically O(n)).
 */
class IntegerLinearProgramming {
 public:
   /**
    * @brief Solves the knapsack problem using ILP (C++/OR-Tools backend).
    * @param pallets List of pallets
    * @param truck Truck (capacity)
    * @param used_pallets Output: selected pallets
    * @param message Output: status and timing info
    * @param timeout_ms Timeout in milliseconds
    * @return Maximum profit
    * @details
    * Time complexity: Exponential in the worst case (depends on solver and
    * instance). Space complexity: O(n)
    */
   unsigned int solve_ilp_cpp(const std::vector<Pallet> &pallets,
                              const Truck &truck,
                              std::vector<Pallet> &used_pallets,
                              std::string &message, unsigned int timeout_ms);
};

#endif  // INTEGER_LINEAR_PROGRAMMING_H
