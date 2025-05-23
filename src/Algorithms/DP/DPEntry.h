#ifndef DP_ENTRY_H
#define DP_ENTRY_H

#include <climits>

struct DPEntry {
  unsigned int profit = 0;
  unsigned int weight = 0;
  unsigned int count = 0;

  bool operator<(const DPEntry &other) const {
    if (profit != other.profit) return profit < other.profit;
    if (weight != other.weight) return weight > other.weight;
    return count > other.count;
  }
};

constexpr DPEntry NOT_COMPUTED_ENTRY = {UINT_MAX, 0, 0};

#endif
