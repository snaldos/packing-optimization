#ifndef VECTOR_DPTABLE_H
#define VECTOR_DPTABLE_H

#include "DPTable.h"
#include <vector>

class VectorDPTable : public DPTable {
 private:
  std::vector<std::vector<unsigned int>> table;

 public:
  VectorDPTable(unsigned int n, unsigned int max_weight);
  unsigned int get(unsigned int i, unsigned int w) const override;
  void set(unsigned int i, unsigned int w, unsigned int value) override;
  std::size_t get_num_entries() const override;
  std::size_t get_memory_usage() const override;
};

#endif // VECTOR_DPTABLE_H
