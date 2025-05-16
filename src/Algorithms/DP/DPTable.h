#ifndef DP_TABLE_H
#define DP_TABLE_H

#include <cstddef>

class DPTable {
 public:
  virtual unsigned int get(unsigned int i, unsigned int w) const = 0;
  virtual void set(unsigned int i, unsigned int w, unsigned int value) = 0;
  virtual std::size_t get_num_entries() const = 0;
  virtual std::size_t get_memory_usage() const = 0;
  virtual ~DPTable() = default;
};

#endif  // DP_TABLE_H
