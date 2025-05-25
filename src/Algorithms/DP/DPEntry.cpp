#include "DPEntry.h"
#include <climits>

// Static member definitions for NOT_COMPUTED
const DPSimpleEntry DPSimpleEntry::NOT_COMPUTED(UINT_MAX);
const DPEntryDraw DPEntryDraw::NOT_COMPUTED(UINT_MAX, 0, 0);
const DPEntryLex DPEntryLex::NOT_COMPUTED(UINT_MAX, 0, 0, {});

// Factory method implementations
std::unique_ptr<DPEntryBase>
DPEntryBase::make_empty(bool draw_condition, bool lexicographical_order) {
  if (!draw_condition)
    return std::make_unique<DPSimpleEntry>(0);
  else if (!lexicographical_order)
    return std::make_unique<DPEntryDraw>(0, 0, 0);
  else
    return std::make_unique<DPEntryLex>(0, 0, 0, std::vector<std::string>{});
}

std::unique_ptr<DPEntryBase>
DPEntryBase::make_not_computed(bool draw_condition,
                               bool lexicographical_order) {
  if (!draw_condition)
    return std::make_unique<DPSimpleEntry>(DPSimpleEntry::NOT_COMPUTED);
  else if (!lexicographical_order)
    return std::make_unique<DPEntryDraw>(DPEntryDraw::NOT_COMPUTED);
  else
    return std::make_unique<DPEntryLex>(DPEntryLex::NOT_COMPUTED);
}
