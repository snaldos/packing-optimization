#ifndef GREEDY_H
#define GREEDY_H

#include <algorithm>
#include <chrono>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"

/*

  - Implement the greedy algorithm studied in class that selects pallets based
  on their weight-to-profit ratio, where the last pallet might not be included
  as one cannot consider a fraction of a pallet.
  - Compare the accuracy and performance of this approximation algorithm with
  the optimal solutions obtained from the exhaustive and dynamic programming
  approaches (using only small datasets).
  - Evaluate the performance and fidelity of the greedy algorithm in the small
  and large data sets.
  - Remember that this problem is not the Fractional Knapsack Problem.

*/

/**
 * @class Greedy
 * @brief Implements a greedy approximation algorithm for the 0/1 Knapsack
 * Problem.
 *
 * Selects pallets based on their profit-to-weight ratio (not fractional
 * knapsack).
 *
 * Time complexity: O(n log n) (for sorting) + O(n) (selection) = O(n log n)
 * Space complexity: O(n) (for sorted copy and output)
 */
class Greedy {
 public:
   /**
    * @brief Solves the knapsack problem using a greedy approximation algorithm.
    * @param pallets List of pallets
    * @param truck Truck (capacity)
    * @param used_pallets Output: selected pallets
    * @param message Output: status and timing info
    * @param timeout_ms Timeout in milliseconds
    * @return Total profit of selected pallets
    * @details
    * Time complexity: O(n log n)
    * Space complexity: O(n)
    */
   unsigned int approx_solve(const std::vector<Pallet> &pallets,
                             const Truck &truck,
                             std::vector<Pallet> &used_pallets,
                             std::string &message, unsigned int timeout_ms);
};

#endif  // GREEDY_H
