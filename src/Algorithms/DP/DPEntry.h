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
  virtual unsigned int get_weight() const { return 0; }
  virtual unsigned int get_count() const { return 0; }
  virtual const std::vector<std::string> &get_ids() const {
    static const std::vector<std::string> empty_ids;
    return empty_ids;
  }
  virtual std::unique_ptr<DPEntryBase> clone() const = 0;
  virtual bool equals(const DPEntryBase &other) const = 0;
  static std::unique_ptr<DPEntryBase> make_empty(bool draw_condition,
                                                 bool lexicographical_order);
  static std::unique_ptr<DPEntryBase>
  make_not_computed(bool draw_condition, bool lexicographical_order);
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
  std::unique_ptr<DPEntryBase> clone() const override {
    return std::make_unique<DPSimpleEntry>(*this);
  }
  bool equals(const DPEntryBase &other) const override {
    return profit == static_cast<const DPSimpleEntry &>(other).profit;
  }
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
  unsigned int get_weight() const override { return weight; }
  unsigned int get_count() const override { return count; }
  std::unique_ptr<DPEntryBase> clone() const override {
    return std::make_unique<DPEntryDraw>(*this);
  }
  bool equals(const DPEntryBase &other) const override {
    const DPEntryDraw &o = static_cast<const DPEntryDraw &>(other);
    return profit == o.profit && weight == o.weight && count == o.count;
  }
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
  unsigned int get_weight() const override { return weight; }
  unsigned int get_count() const override { return count; }
  const std::vector<std::string> &get_ids() const override { return ids; }
  std::unique_ptr<DPEntryBase> clone() const override {
    return std::make_unique<DPEntryLex>(*this);
  }
  bool equals(const DPEntryBase &other) const override {
    const DPEntryLex &o = static_cast<const DPEntryLex &>(other);
    return profit == o.profit && weight == o.weight && count == o.count &&
           ids == o.ids;
  }
  static const DPEntryLex NOT_COMPUTED;
};

#endif
