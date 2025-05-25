#include "HashMapDPTable.h"
#include <stdexcept>

namespace {
const DPSimpleEntry not_computed_simple(UINT_MAX);
const DPEntryDraw not_computed_regular(UINT_MAX, 0, 0);
const DPEntryLex not_computed_lex(UINT_MAX, 0, 0, {});
} // namespace

HashMapDPTable::HashMapDPTable(
    std::function<std::unique_ptr<DPEntryBase>()> entry_factory)
    : entry_factory(std::move(entry_factory)) {
  // Probe the entry type to determine its size
  if (this->entry_factory) {
    auto probe = this->entry_factory();
    if (dynamic_cast<DPSimpleEntry *>(probe.get()))
      entry_size = sizeof(unsigned int);
    else if (dynamic_cast<DPEntryDraw *>(probe.get()))
      entry_size = 3 * sizeof(unsigned int);
    else if (dynamic_cast<DPEntryLex *>(probe.get()))
      entry_size = 3 * sizeof(unsigned int) + sizeof(std::vector<std::string>);
    else
      entry_size = sizeof(std::unique_ptr<DPEntryBase>);
  } else {
    entry_size = sizeof(std::unique_ptr<DPEntryBase>);
  }
}

const DPEntryBase &HashMapDPTable::get(unsigned int i, unsigned int w) const {
  auto it = table.find({i, w});
  if (it != table.end())
    return *(it->second);
  if (entry_factory) {
    auto probe = entry_factory();
    if (dynamic_cast<DPSimpleEntry *>(probe.get()))
      return not_computed_simple;
    if (dynamic_cast<DPEntryDraw *>(probe.get()))
      return not_computed_regular;
    if (dynamic_cast<DPEntryLex *>(probe.get()))
      return not_computed_lex;
  }
  throw std::runtime_error("Unknown DPEntryBase type in HashMapDPTable::get");
}

void HashMapDPTable::set(unsigned int i, unsigned int w,
                         std::unique_ptr<DPEntryBase> entry) {
  table[{i, w}] = std::move(entry);
}

std::size_t HashMapDPTable::get_num_entries() const { return table.size(); }

std::size_t HashMapDPTable::get_memory_usage() const {
  // Each entry: value + key (pair of unsigned int)
  std::size_t entry_mem =
      table.size() * (entry_size + 2 * sizeof(unsigned int));
  // Hash table bucket array: each bucket is a pointer
  std::size_t bucket_mem = table.bucket_count() * sizeof(void *);
  return entry_mem + bucket_mem;
}
