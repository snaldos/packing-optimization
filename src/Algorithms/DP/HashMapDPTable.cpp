#include "HashMapDPTable.h"
#include "DPEntry.h"

HashMapDPTable::HashMapDPTable(bool lexicographical_order)
    : lexicographical_order(lexicographical_order) {}

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
  size_t entry_size = sizeof(Entry);
  if (!lexicographical_order) {
    entry_size -= sizeof(std::vector<std::string>);
  }
  // Add the bucket array size (each bucket is a pointer)
  size_t bucket_mem = table.bucket_count() * sizeof(void*);
  return get_num_entries() * entry_size + bucket_mem;
}
