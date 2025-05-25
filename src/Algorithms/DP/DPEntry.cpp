#include "DPEntry.h"
#include <climits>

// Static member definitions for NOT_COMPUTED
const DPSimpleEntry DPSimpleEntry::NOT_COMPUTED(UINT_MAX);
const DPEntryDraw DPEntryDraw::NOT_COMPUTED(UINT_MAX, 0, 0);
const DPEntryLex DPEntryLex::NOT_COMPUTED(UINT_MAX, 0, 0, {});
