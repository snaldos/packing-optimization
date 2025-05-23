#ifndef HASHMAP_DPTABLE_H
#define HASHMAP_DPTABLE_H

#include <climits>
#include <unordered_map>
#include <utility>

#include "DPEntry.h"
#include "DPTable.h"

constexpr unsigned int NOT_COMPUTED = UINT_MAX;

struct PairHash {
  std::size_t operator()(const std::pair<unsigned int, unsigned int>& p) const {
    return p.first * 31 + p.second;
  }
};

/**
 * @class HashMapDPTable
 * @brief Concrete DP table implementation using a hash map for top-down DP
 * (memoization).
 *
 * Stores subproblem solutions in a sparse hash map keyed by (i, w) pairs.
 * Used for top-down dynamic programming approaches to knapsack.
 *
 * Time complexity for access/set: O(1) average (hash map)
 * Space complexity: O(s), where s is the number of unique (i, w) states.
 */
class HashMapDPTable : public DPTable {
 private:
   std::unordered_map<std::pair<unsigned int, unsigned int>, DPEntry, PairHash>
       table;

 public:
   /**
    * @brief Construct a new HashMapDPTable object.
    */
   HashMapDPTable();

   /**
    * @brief Get the value stored for subproblem (i, w).
    * @param i Item index
    * @param w Remaining capacity
    * @return Value for subproblem (i, w), or NOT_COMPUTED if not set
    */
   DPEntry get(unsigned int i, unsigned int w) const override;

   /**
    * @brief Set the value for subproblem (i, w).
    * @param i Item index
    * @param w Remaining capacity
    * @param entry Value to store
    */
   void set(unsigned int i, unsigned int w, const DPEntry &entry) override;

   /**
    * @brief Get the number of entries stored in the table.
    * @return Number of entries
    */
   std::size_t get_num_entries() const override;

   /**
    * @brief Get the estimated memory usage of the table in bytes.
    * @return Memory usage in bytes
    */
   std::size_t get_memory_usage() const override;
};

#endif  // HASHMAP_DPTABLE_H
