#ifndef ILP_BRIDGE_PY_H
#define ILP_BRIDGE_PY_H

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

/**
 * @class ILPBridgePy
 * @brief Bridges C++ and Python to solve the 0/1 Knapsack Problem using ILP
 * (via PuLP).
 *
 * Serializes the problem to JSON, calls a Python script to solve it using PuLP,
 * and parses the result.
 *
 * Time complexity: Depends on the Python ILP solver; exponential in the worst
 * case, but often efficient for moderate n. Space complexity: Depends on the
 * solver's internal representation (typically O(n)).
 */
class ILPBridgePy {
 public:
   /**
    * @brief Solves the knapsack problem using ILP (Python/PuLP backend).
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
   unsigned int solve_ilp_py(const std::vector<Pallet> &pallets,
                             const Truck &truck,
                             std::vector<Pallet> &used_pallets,
                             std::string &message, unsigned int timeout_ms);
};

#endif  // ILPBRIDGEPY_H
