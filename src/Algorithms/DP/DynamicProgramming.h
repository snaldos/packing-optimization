#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include <algorithm>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"
#include "DPTable.h"
#include "HashMapDPTable.h"
#include "VectorDPTable.h"

enum class TableType { Vector, HashMap };

/**
 * @class DynamicProgramming
 * @brief Implements dynamic programming algorithms for the 0/1 Knapsack
 * Problem.
 *
 * Supports both bottom-up (vector table) and top-down (hashmap memoization)
 * approaches.
 *
 * - DP Vector: O(nW) time, O(nW) space (can reconstruct solution).
 * - DP HashMap: O(s) time, O(s) space, where s is the number of unique (i, w)
 * states (sparse for some datasets).
 * - DP Optimized (2 rows): O(nW) time, O(W) space (only computes max profit, no
 * reconstruction).
 */
class DynamicProgramming {
 private:
   /**
    * @brief Creates a DP table of the specified type.
    * @param type TableType::Vector or TableType::HashMap
    * @param n Number of items
    * @param max_weight Maximum capacity
    * @return Unique pointer to DPTable
    */
   std::unique_ptr<DPTable> create_table(TableType type, unsigned int n,
                                         unsigned int max_weight);

   /**
    * @brief Top-down DP with memoization (HashMap), computes only max profit.
    * @param pallets List of pallets
    * @param dp DPTable (HashMap)
    * @param i Current item index
    * @param w Remaining capacity
    * @param deadline Timeout deadline
    * @param timed_out Set to true if timeout occurs
    * @return Maximum profit
    * @details
    * Time complexity: O(s), where s is the number of unique (i, w) states.
    * Space complexity: O(s).
    */
   unsigned int dp_solve_top_down(
       const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
       unsigned int i, unsigned int w,
       std::chrono::steady_clock::time_point deadline, bool &timed_out);

   /**
    * @brief Top-down DP with memoization (HashMap), reconstructs used pallets.
    * @param pallets List of pallets
    * @param dp DPTable (HashMap)
    * @param i Current item index
    * @param w Remaining capacity
    * @param used_pallets Output: selected pallets
    * @param deadline Timeout deadline
    * @param timed_out Set to true if timeout occurs
    * @return Maximum profit
    * @details
    * Time complexity: O(s), where s is the number of unique (i, w) states.
    * Space complexity: O(s).
    */
   unsigned int dp_solve_top_down(
       const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
       unsigned int i, unsigned int w, std::vector<Pallet> &used_pallets,
       std::chrono::steady_clock::time_point deadline, bool &timed_out);

   /**
    * @brief Bottom-up DP (vector table), reconstructs used pallets.
    * @param pallets List of pallets
    * @param dp DPTable (Vector)
    * @param n Number of items
    * @param max_weight Maximum capacity
    * @param used_pallets Output: selected pallets
    * @param deadline Timeout deadline
    * @param timed_out Set to true if timeout occurs
    * @return Maximum profit
    * @details
    * Time complexity: O(nW)
    * Space complexity: O(nW)
    */
   unsigned int dp_solve_bottom_up(
       const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
       unsigned int n, unsigned int max_weight,
       std::vector<Pallet> &used_pallets,
       std::chrono::steady_clock::time_point deadline, bool &timed_out);

 public:
   /**
    * @brief Solves the knapsack problem using DP (vector or hashmap),
    * reconstructs solution.
    * @param pallets List of pallets
    * @param truck Truck (capacity)
    * @param used_pallets Output: selected pallets
    * @param type TableType::Vector or TableType::HashMap
    * @param message Output: status and timing info
    * @param timeout_ms Timeout in milliseconds
    * @return Maximum profit
    */
   unsigned int dp_solve(const std::vector<Pallet> &pallets, const Truck &truck,
                         std::vector<Pallet> &used_pallets, TableType type,
                         std::string &message, unsigned int timeout_ms);

   /**
    * @brief Solves the knapsack problem using DP optimized (2 rolling rows),
    * only max profit.
    * @param pallets List of pallets
    * @param truck Truck (capacity)
    * @param message Output: status and timing info
    * @param timeout_ms Timeout in milliseconds
    * @return Maximum profit
    * @details
    * Time complexity: O(nW)
    * Space complexity: O(W)
    */
   unsigned int dp_solve(const std::vector<Pallet> &pallets, const Truck &truck,
                         std::string &message, unsigned int timeout_ms);
};

#endif  // DYNAMIC_PROGRAMMING_H
