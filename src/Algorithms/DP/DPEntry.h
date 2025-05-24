#ifndef DP_ENTRY_H
#define DP_ENTRY_H

#include <climits>
#include <string>
#include <vector>

/**
 * @struct DPEntry
 * @brief Represents a single entry in the dynamic programming table for the
 * knapsack problem.
 *
 * Stores the total profit, total weight, number of pallets, and the sorted
 * vector of pallet IDs used to reach this DP state. The comparison operator
 * implements all tie-breaking rules: maximize profit, minimize weight, minimize
 * count, and finally select the lexicographically smallest set of pallet IDs.
 */
struct DPEntry {
  /**
   * @brief Total profit for this DP state.
   */
  unsigned int profit = 0;
  /**
   * @brief Total weight for this DP state.
   */
  unsigned int weight = 0;
  /**
   * @brief Number of pallets used in this DP state.
   */
  unsigned int count = 0;
  /**
   * @brief Sorted vector of pallet IDs used in this DP state (for
   * lexicographical tie-breaking).
   */
  std::vector<std::string> ids;

  /**
   * @brief Comparison operator for DPEntry.
   *
   * Implements the following tie-breaking rules:
   * 1. Maximize profit
   * 2. Minimize weight
   * 3. Minimize number of pallets
   * 4. Lexicographically smallest set of pallet IDs
   *
   * @param other The DPEntry to compare against.
   * @return true if this entry is considered worse than other (for use in
   * std::max).
   */
  bool operator<(const DPEntry &other) const {
    if (profit != other.profit) return profit < other.profit;
    if (weight != other.weight) return weight > other.weight;
    if (count != other.count)
      return count > other.count;
    return ids > other.ids; // Lexicographical comparison
  }
};

/**
 * @brief Sentinel value for an uncomputed DPEntry (profit set to UINT_MAX).
 */
const DPEntry NOT_COMPUTED_ENTRY = {UINT_MAX, 0, 0, {}};

#endif
