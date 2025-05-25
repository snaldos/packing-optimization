#ifndef HASHMAP_DPTABLE_H
#define HASHMAP_DPTABLE_H

#include <climits>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

#include "DPEntry.h"
#include "DPTable.h"

/**
 * @struct PairHash
 * @brief Hash function for std::pair<unsigned int, unsigned int> to be used in
 * std::unordered_map.
 *
 * Enables the use of (i, w) pairs as keys in the DP table's hash map by
 * providing a simple hash combining the two unsigned integers. This is required
 * for memoization in top-down dynamic programming approaches.
 */
struct PairHash {
  std::size_t operator()(const std::pair<unsigned int, unsigned int> &p) const {
    return p.first * 31 + p.second;
  }
};

/**
 * @class HashMapDPTable
 * @brief Concrete DP table implementation using a hash map for top-down DP
 * (memoization).
 *
 * Templated on the DP entry type (DPSimpleEntry, DPEntry, DPEntryLex).
 */
class HashMapDPTable : public DPTable {
private:
  std::unordered_map<std::pair<unsigned int, unsigned int>,
                     std::unique_ptr<DPEntryBase>, PairHash>
      table;
  // Factory for creating new entries
  std::function<std::unique_ptr<DPEntryBase>()> entry_factory;

public:
  /**
   * @brief Construct a new HashMapDPTable object.
   * @param entry_factory Factory function to create DPEntryBase objects
   */
  HashMapDPTable(std::function<std::unique_ptr<DPEntryBase>()> entry_factory);

  /**
   * @brief Get the value stored for subproblem (i, w).
   * @param i Item index
   * @param w Remaining capacity
   * @return Value for subproblem (i, w), or NOT_COMPUTED_ENTRY if not set
   */
  const DPEntryBase &get(unsigned int i, unsigned int w) const override;

  /**
   * @brief Set the value for subproblem (i, w).
   * @param i Item index
   * @param w Remaining capacity
   * @param entry Value to store
   */
  void set(unsigned int i, unsigned int w,
           std::unique_ptr<DPEntryBase> entry) override;

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

#endif // HASHMAP_DPTABLE_H
