#include "VectorDPTable.h"

VectorDPTable::VectorDPTable(unsigned int n, unsigned int max_weight)
    : table(n + 1, std::vector<unsigned int>(max_weight + 1, 0)) {}

unsigned int VectorDPTable::get(unsigned int i, unsigned int w) const {
  return table[i][w];
}

void VectorDPTable::set(unsigned int i, unsigned int w, unsigned int value) {
  table[i][w] = value;
}

std::size_t VectorDPTable::get_num_entries() const {
  return table.size() * table[0].size();
}

std::size_t VectorDPTable::get_memory_usage() const {
  if (table.empty()) return 0;
  return get_num_entries() * sizeof(unsigned int);
}
