#ifndef VECTOR_DPTABLE_H
#define VECTOR_DPTABLE_H

#include "DPEntry.h"
#include "DPTable.h"
#include <vector>

/**
 * @class VectorDPTable
 * @brief Concrete DP table implementation using a 2D vector for bottom-up DP.
 *
 * Stores subproblem solutions in a dense (n+1) x (max_weight+1) table.
 * Used for classic bottom-up dynamic programming approaches to knapsack.
 *
 * Time complexity for access/set: O(1)
 * Space complexity: O(nW)
 */
class VectorDPTable : public DPTable {
 private:
   std::vector<std::vector<DPEntry>> table;

 public:
   /**
    * @brief Construct a new VectorDPTable object.
    * @param n Number of items
    * @param max_weight Maximum capacity
    */
   VectorDPTable(unsigned int n, unsigned int max_weight);

   /**
    * @brief Get the value stored for subproblem (i, w).
    * @param i Item index
    * @param w Remaining capacity
    * @return Value for subproblem (i, w)
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

#endif // VECTOR_DPTABLE_H
