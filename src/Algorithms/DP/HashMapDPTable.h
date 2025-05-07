#ifndef HASHMAP_DPTABLE_H
#define HASHMAP_DPTABLE_H

#include <climits>
#include <unordered_map>
#include <utility>

#include "DPTable.h"

constexpr unsigned int NOT_COMPUTED = UINT_MAX;

struct PairHash {
  std::size_t operator()(const std::pair<unsigned int, unsigned int>& p) const {
    return p.first * 31 + p.second;
  }
};

class HashMapDPTable : public DPTable {
 private:
  std::unordered_map<std::pair<unsigned int, unsigned int>, unsigned int,
                     PairHash>
      table;

 public:
  HashMapDPTable();
  unsigned int get(unsigned int i, unsigned int w) const override;
  void set(unsigned int i, unsigned int w, unsigned int value) override;
  std::size_t get_num_entries() const override;
  std::size_t get_memory_usage() const override;
};

#endif  // HASHMAP_DPTABLE_H
