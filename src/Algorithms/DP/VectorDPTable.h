#ifndef VECTOR_DPTABLE_H
#define VECTOR_DPTABLE_H

#include "DPEntry.h"
#include "DPTable.h"
#include <functional>
#include <memory>
#include <vector>

/**
 * @class VectorDPTable
 * @brief Concrete DP table implementation using a 2D vector for bottom-up DP.
 */
class VectorDPTable : public DPTable {
 private:
   std::vector<std::vector<std::unique_ptr<DPEntryBase>>>
       table; ///< 2D vector to store DP entries
   std::function<std::unique_ptr<DPEntryBase>()>
       entry_factory; ///< Factory function for creating DP entries
   std::size_t entry_size = 0; ///< Size of the DP entry type

 public:
   /**
    * @brief Construct a new VectorDPTable object.
    * @param n Number of items
    * @param max_weight Maximum capacity
    * @param entry_factory Factory function to create DPEntryBase objects
    */
   VectorDPTable(unsigned int n, unsigned int max_weight,
                 std::function<std::unique_ptr<DPEntryBase>()> entry_factory);

   /**
    * @brief Get a const reference to the DP entry at the specified indices.
    * @param i Index for the item
    * @param w Index for the weight
    * @return const DPEntryBase& Reference to the DP entry
    */
   const DPEntryBase &get(unsigned int i, unsigned int w) const override;

   /**
    * @brief Set the DP entry at the specified indices.
    * @param i Index for the item
    * @param w Index for the weight
    * @param entry Unique pointer to the DP entry
    */
   void set(unsigned int i, unsigned int w,
            std::unique_ptr<DPEntryBase> entry) override;

   /**
    * @brief Get the total number of entries in the DP table.
    * @return std::size_t Total number of entries
    */
   std::size_t get_num_entries() const override;

   /**
    * @brief Get the total memory usage of the DP table.
    * @return std::size_t Total memory usage in bytes
    */
   std::size_t get_memory_usage() const override;
};

#endif // VECTOR_DPTABLE_H
