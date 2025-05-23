#include "HashMapDPTable.h"
#include "DPEntry.h"

HashMapDPTable::HashMapDPTable() {}

DPEntry HashMapDPTable::get(unsigned int i, unsigned int w) const {
  auto it = table.find({i, w});
  return it != table.end() ? it->second : NOT_COMPUTED_ENTRY;
}

void HashMapDPTable::set(unsigned int i, unsigned int w, const DPEntry &entry) {
  table[{i, w}] = entry;
}

std::size_t HashMapDPTable::get_num_entries() const { return table.size(); }

std::size_t HashMapDPTable::get_memory_usage() const {
  using Entry = std::pair<std::pair<unsigned int, unsigned int>, DPEntry>;
  return get_num_entries() * sizeof(Entry);
}
