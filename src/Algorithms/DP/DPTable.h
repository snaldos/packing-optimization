#include "DPEntry.h"

#ifndef DP_TABLE_H
#define DP_TABLE_H

#include <cstddef>
#include <memory>

/**
 * @class DPTable
 * @brief Abstract interface for dynamic programming tables used in knapsack
 * algorithms.
 */
class DPTable {
 public:
   /**
    * @brief Get the value stored for subproblem (i, w).
    * @param i Item index
    * @param w Remaining capacity
    * @return Value for subproblem (i, w), or a sentinel if not set
    */
   virtual const DPEntryBase &get(unsigned int i, unsigned int w) const = 0;

   /**
    * @brief Set the value for subproblem (i, w).
    * @param i Item index
    * @param w Remaining capacity
    * @param entry Value to store
    */
   virtual void set(unsigned int i, unsigned int w,
                    std::unique_ptr<DPEntryBase> entry) = 0;

   /**
    * @brief Get the number of entries stored in the table.
    * @return Number of entries
    */
   virtual std::size_t get_num_entries() const = 0;

   /**
    * @brief Get the estimated memory usage of the table in bytes.
    * @return Memory usage in bytes
    */
   virtual std::size_t get_memory_usage() const = 0;

   /**
    * @brief Virtual destructor for safe cleanup.
    */
   virtual ~DPTable() = default;
};

#endif // DP_TABLE_H
