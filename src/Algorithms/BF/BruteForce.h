#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"

/**
 * @class BruteForce
 * @brief Implements brute-force and backtracking algorithms for the 0/1
 * Knapsack Problem.
 *
 * - Brute-force (explicit subset generation): O(2^n * n) time, O(n) space for
 * best solution.
 * - Backtracking: O(2^n) time in worst case, but can be faster with pruning;
 * O(n) space for recursion and best solution.
 */
class BruteForce {
 public:
   /**
    * @brief Solves the knapsack problem using brute force (backtracking).
    * @param pallets List of pallets
    * @param truck Truck (capacity)
    * @param used_pallets Output: selected pallets
    * @param message Output: status and timing info
    * @param timeout_ms Timeout in milliseconds
    * @return Maximum profit
    * @details
    * Time complexity: O(2^n) (worst case)
    * Space complexity: O(n)
    */
   unsigned int bt_solve(std::vector<Pallet> pallets, const Truck &truck,
                         std::vector<Pallet> &used_pallets,
                         std::string &message, unsigned int timeout_ms);

   /**
    * @brief Solves the knapsack problem using brute force (explicit subset
    * generation).
    * @param pallets List of pallets
    * @param truck Truck (capacity)
    * @param used_pallets Output: selected pallets
    * @param message Output: status and timing info
    * @param timeout_ms Timeout in milliseconds
    * @return Maximum profit
    * @details
    * Time complexity: O(2^n * n)
    * Space complexity: O(n)
    */
   unsigned int bf_solve(const std::vector<Pallet> &pallets, const Truck &truck,
                         std::vector<Pallet> &used_pallets,
                         std::string &message, unsigned int timeout_ms);

 private:
   /**
    * @brief Helper function for recursive brute force (backtracking).
    * @param pallets List of pallets
    * @param index Current item index
    * @param curr_weight Current total weight
    * @param curr_value Current total value
    * @param max_weight Maximum capacity
    * @param curr_used Current selection vector
    * @param best_used Best selection vector
    * @param best_value Best value found so far
    * @param deadline Timeout deadline
    * @param timed_out Set to true if timeout occurs
    */
   void bt_helper(const std::vector<Pallet> &pallets, unsigned int index,
                  unsigned int curr_weight, unsigned int curr_value,
                  unsigned int max_weight, std::vector<bool> &curr_used,
                  std::vector<bool> &best_used, unsigned int &best_value,
                  std::chrono::steady_clock::time_point deadline,
                  bool &timed_out);

   /**
    * @brief Estimates an upper bound for the current subproblem (optional, for
    * pruning).
    * @param pallets List of pallets
    * @param index Current item index
    * @param curr_weight Current total weight
    * @param curr_value Current total value
    * @param max_weight Maximum capacity
    * @return Upper bound on achievable value
    */
   double estimate_upper_bound(const std::vector<Pallet> &pallets,
                               unsigned int index, unsigned int curr_weight,
                               unsigned int curr_value,
                               unsigned int max_weight);
};

#endif  // BRUTE_FORCE_H
