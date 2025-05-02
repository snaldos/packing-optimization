#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../DataStructures/Pallet.h"
#include "../DataStructures/Truck.h"

/*

- Implement a dynamic programming solution and pay special attention to the data
structure used to store the dynamic programming table, as it can become very
large for bigger datasets.
- Evaluate different data structure alternatives (e.g., arrays, hash maps) and
consider implementing a custom solution if necessary.
- Analyze the performance of this approach and observe its limitations.

*/

enum class TableType { Vector, HashMap };

class DPTable {
 public:
  virtual unsigned int get(unsigned int i, unsigned int w) const = 0;
  virtual void set(unsigned int i, unsigned int w, unsigned int value) = 0;
  virtual std::size_t get_memory_usage() const = 0;
  virtual ~DPTable() = default;
};

class VectorDPTable : public DPTable {
  /*

    ⚡ Faster:

    Constant-time array indexing with no hashing overhead.

    💾 More Memory Use:

    Allocates the entire (n+1) × (W+1) table up front.

    Even unused cells consume memory.

  */
 private:
  std::vector<std::vector<unsigned int>> table;

 public:
  VectorDPTable(unsigned int n, unsigned int max_weight)
      : table(n + 1, std::vector<unsigned int>(max_weight + 1, 0)) {}

  unsigned int get(unsigned int i, unsigned int w) const override {
    return table[i][w];
  }

  void set(unsigned int i, unsigned int w, unsigned int value) override {
    table[i][w] = value;
  }

  std::size_t get_memory_usage() const override {
    return table.size() * sizeof(unsigned int);
  }
};

// Custom hash for pair key
struct PairHash {
  std::size_t operator()(const std::pair<unsigned int, unsigned int>& p) const {
    return std::hash<unsigned int>()(p.first) ^
           (std::hash<unsigned int>()(p.second) << 1);
  }
};

class HashMapDPTable : public DPTable {
  /*

    ⏱️ Slightly Slower:

    Every access (get or set) involves:

    Hashing the key (i, w)

    Looking up in a hash table (not constant time in practice due to collisions
    and chaining/probing)

    More overhead than direct array indexing.

    🧠 Potentially Less Space:

    Only stores entries that are actually used.

    If the DP table is sparse (e.g. due to weight constraints or pruning), the
    savings can be significant.

    Especially useful when W is large but many combinations are irrelevant or
    unreachable.

  */
 private:
  std::unordered_map<std::pair<unsigned int, unsigned int>, unsigned int,
                     PairHash>
      table;

 public:
  HashMapDPTable() {
    // Optional: reserve space if expected number of entries is known
    // table.reserve(...);
  }

  unsigned int get(unsigned int i, unsigned int w) const override {
    auto it = table.find({i, w});
    return it != table.end() ? it->second : 0;
  }

  void set(unsigned int i, unsigned int w, unsigned int value) override {
    table[{i, w}] = value;
  }

  std::size_t get_memory_usage() const override {
    // Each entry in the hash map consists of a pair (i, w) and the value
    // The size of the hash map itself is not trivial to calculate, but we can
    // estimate it based on the number of entries and the size of the hash
    // table
    // This is a rough estimate and may vary based on the implementation of
    // std::unordered_map
    // and the load factor used
    // Note: This does not account for the overhead of the hash table itself
    // (buckets, etc.)
    return table.size() * (sizeof(std::pair<unsigned int, unsigned int>) +
                           sizeof(unsigned int));
  }
};

class DynamicProgramming {
 private:
  std::unique_ptr<DPTable> create_table(TableType type, unsigned int n,
                                        unsigned int max_weight);

 public:
  unsigned int dp_solve(const std::vector<Pallet>& pallets, const Truck& truck,
                        std::vector<Pallet>& used_pallets, TableType type,
                        std::string& message);
};

#endif  // DYNAMICPROGRAMMING_H
