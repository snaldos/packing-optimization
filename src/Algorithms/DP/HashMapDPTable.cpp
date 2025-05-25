#include "HashMapDPTable.h"
#include <stdexcept>

namespace {
const DPSimpleEntry not_computed_simple(UINT_MAX);
const DPEntryDraw not_computed_regular(UINT_MAX, 0, 0);
const DPEntryLex not_computed_lex(UINT_MAX, 0, 0, {});
} // namespace

HashMapDPTable::HashMapDPTable(
    bool /*lexicographical_order*/,
    std::function<std::unique_ptr<DPEntryBase>()> entry_factory)
    : entry_factory(std::move(entry_factory)) {}

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
  return table.size() * sizeof(std::unique_ptr<DPEntryBase>);
}
