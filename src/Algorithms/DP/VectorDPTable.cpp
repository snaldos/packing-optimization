#include "VectorDPTable.h"
#include <stdexcept>

namespace {
const DPSimpleEntry not_computed_simple(UINT_MAX);
const DPEntryDraw not_computed_regular(UINT_MAX, 0, 0);
const DPEntryLex not_computed_lex(UINT_MAX, 0, 0, {});
} // namespace

VectorDPTable::VectorDPTable(
    unsigned int n, unsigned int max_weight,
    std::function<std::unique_ptr<DPEntryBase>()> entry_factory)
    : entry_factory(std::move(entry_factory)) {
  table.resize(n + 1);
  for (auto &row : table) {
    row.resize(max_weight + 1);
    for (auto &cell : row) {
      if (this->entry_factory)
        cell = this->entry_factory();
    }
  }
}

const DPEntryBase &VectorDPTable::get(unsigned int i, unsigned int w) const {
  if (table[i][w])
    return *table[i][w];
  if (entry_factory) {
    auto probe = entry_factory();
    if (dynamic_cast<DPSimpleEntry *>(probe.get()))
      return not_computed_simple;
    if (dynamic_cast<DPEntryDraw *>(probe.get()))
      return not_computed_regular;
    if (dynamic_cast<DPEntryLex *>(probe.get()))
      return not_computed_lex;
  }
  throw std::runtime_error("Unknown DPEntryBase type in VectorDPTable::get");
}

void VectorDPTable::set(unsigned int i, unsigned int w,
                        std::unique_ptr<DPEntryBase> entry) {
  table[i][w] = std::move(entry);
}

std::size_t VectorDPTable::get_num_entries() const {
  std::size_t count = 0;
  for (const auto &row : table)
    count += row.size();
  return count;
}

std::size_t VectorDPTable::get_memory_usage() const {
  std::size_t count = get_num_entries();
  return count * sizeof(std::unique_ptr<DPEntryBase>);
}
