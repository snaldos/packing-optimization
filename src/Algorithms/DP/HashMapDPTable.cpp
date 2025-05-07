#include "HashMapDPTable.h"

HashMapDPTable::HashMapDPTable() {
  // Optionally reserve space if needed
}

unsigned int HashMapDPTable::get(unsigned int i, unsigned int w) const {
  auto it = table.find({i, w});
  return it != table.end() ? it->second : NOT_COMPUTED;
}

void HashMapDPTable::set(unsigned int i, unsigned int w, unsigned int value) {
  table[{i, w}] = value;
}

std::size_t HashMapDPTable::get_num_entries() const { return table.size(); }

std::size_t HashMapDPTable::get_memory_usage() const {
  using Entry = std::pair<std::pair<unsigned int, unsigned int>, unsigned int>;
  return get_num_entries() * sizeof(Entry);
}
