#include "VectorDPTable.h"
#include "DPEntry.h"

VectorDPTable::VectorDPTable(unsigned int n, unsigned int max_weight)
    : table(n + 1, std::vector<DPEntry>(max_weight + 1, DPEntry{})) {}

DPEntry VectorDPTable::get(unsigned int i, unsigned int w) const {
  return table[i][w];
}

void VectorDPTable::set(unsigned int i, unsigned int w, const DPEntry &entry) {
  table[i][w] = entry;
}

std::size_t VectorDPTable::get_num_entries() const {
  return table.size() * table[0].size();
}

std::size_t VectorDPTable::get_memory_usage() const {
  if (table.empty()) return 0;
  return get_num_entries() * sizeof(DPEntry);
}
