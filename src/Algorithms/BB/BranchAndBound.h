#pragma once
#include <vector>
#include <string>
#include <chrono>
#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"

/**
 * @class BranchAndBound
 * @brief Implements the branch-and-bound algorithm for the 0/1 Knapsack
 * Problem.
 *
 * Uses upper bound estimation (fractional knapsack) to prune the search space.
 *
 * Time complexity: O(2^n) in the worst case, but typically much faster due to
 * pruning. Space complexity: O(n) for recursion and solution vectors.
 */
class BranchAndBound {
public:
  /**
   * @brief Solves the knapsack problem using branch-and-bound.
   * @param pallets List of pallets
   * @param truck Truck (capacity)
   * @param used_pallets Output: selected pallets
   * @param message Output: status and timing info
   * @param timeout_ms Timeout in milliseconds
   * @return Maximum profit
   * @details
   * Time complexity: O(2^n) worst case, but usually much less due to pruning.
   * Space complexity: O(n)
   */
  unsigned int bb_solve(std::vector<Pallet> pallets, const Truck &truck,
                        std::vector<Pallet> &used_pallets, std::string &message,
                        unsigned int timeout_ms);
private:
  /**
   * @brief Estimates an upper bound for the current subproblem using fractional
   * knapsack.
   * @param pallets List of pallets
   * @param index Current item index
   * @param curr_weight Current total weight
   * @param curr_value Current total value
   * @param max_weight Maximum capacity
   * @return Upper bound on achievable value
   */
  double estimate_upper_bound(const std::vector<Pallet> &pallets,
                              unsigned int index, unsigned int curr_weight,
                              unsigned int curr_value, unsigned int max_weight);
  /**
   * @brief Helper function for recursive branch-and-bound.
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
  void bb_helper(const std::vector<Pallet> &pallets, unsigned int index,
                 unsigned int curr_weight, unsigned int curr_value,
                 unsigned int max_weight, std::vector<bool> &curr_used,
                 std::vector<bool> &best_used, unsigned int &best_value,
                 std::chrono::steady_clock::time_point deadline,
                 bool &timed_out);
};
