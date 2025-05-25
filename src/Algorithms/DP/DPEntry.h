#ifndef DP_ENTRY_H
#define DP_ENTRY_H

#include <climits>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Base class for DP table entries (for type erasure/polymorphism).
 */
class DPEntryBase {
public:
  virtual ~DPEntryBase() = default;
  virtual bool operator<(const DPEntryBase &other) const = 0;
  virtual unsigned int get_profit() const = 0;
};

/**
 * @brief Simple DP entry: only profit (for draw_condition == false).
 */
class DPSimpleEntry : public DPEntryBase {
public:
  unsigned int profit = 0;
  DPSimpleEntry() = default;
  explicit DPSimpleEntry(unsigned int profit) : profit(profit) {}
  bool operator<(const DPEntryBase &other) const override {
    return profit < static_cast<const DPSimpleEntry &>(other).profit;
  }
  unsigned int get_profit() const override { return profit; }
  static const DPSimpleEntry NOT_COMPUTED;
};

/**
 * @brief Regular DP entry: profit, weight, count (for draw_condition == true,
 * lexicographical_order == false).
 */
class DPEntryDraw : public DPEntryBase {
public:
  unsigned int profit = 0;
  unsigned int weight = 0;
  unsigned int count = 0;
  DPEntryDraw() = default;
  DPEntryDraw(unsigned int profit, unsigned int weight, unsigned int count)
      : profit(profit), weight(weight), count(count) {}
  bool operator<(const DPEntryBase &other) const override {
    const DPEntryDraw &o = static_cast<const DPEntryDraw &>(other);
    if (profit != o.profit)
      return profit < o.profit;
    if (weight != o.weight)
      return weight > o.weight;
    return count > o.count;
  }
  unsigned int get_profit() const override { return profit; }
  static const DPEntryDraw NOT_COMPUTED;
};

/**
 * @brief Lexicographical DP entry: profit, weight, count, ids (for
 * draw_condition == true, lexicographical_order == true).
 */
class DPEntryLex : public DPEntryBase {
public:
  unsigned int profit = 0;
  unsigned int weight = 0;
  unsigned int count = 0;
  std::vector<std::string> ids;
  DPEntryLex() = default;
  DPEntryLex(unsigned int profit, unsigned int weight, unsigned int count,
             const std::vector<std::string> &ids)
      : profit(profit), weight(weight), count(count), ids(ids) {}
  bool operator<(const DPEntryBase &other) const override {
    const DPEntryLex &o = static_cast<const DPEntryLex &>(other);
    if (profit != o.profit)
      return profit < o.profit;
    if (weight != o.weight)
      return weight > o.weight;
    if (count != o.count)
      return count > o.count;
    return ids > o.ids;
  }
  unsigned int get_profit() const override { return profit; }
  static const DPEntryLex NOT_COMPUTED;
};

#endif
