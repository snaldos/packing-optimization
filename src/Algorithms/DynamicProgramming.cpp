#include "DynamicProgramming.h"

std::unique_ptr<DPTable> DynamicProgramming::create_table(
    TableType type, unsigned int n, unsigned int max_weight) {
  if (type == TableType::Vector)
    return std::make_unique<VectorDPTable>(n, max_weight);
  else
    return std::make_unique<HashMapDPTable>();
}

unsigned int DynamicProgramming::dp_solve(const std::vector<Pallet>& pallets,
                                          const Truck& truck,
                                          std::vector<Pallet>& used_pallets,
                                          TableType type,
                                          std::string& message) {
  auto start_time = std::chrono::high_resolution_clock::now();

  auto dp = create_table(type, pallets.size(), truck.get_capacity());
  unsigned int n = pallets.size();
  unsigned int max_weight = truck.get_capacity();

  for (unsigned int i = 1; i <= n; i++) {
    for (unsigned int w = 0; w <= max_weight; w++) {
      if (pallets[i - 1].get_weight() <= w) {
        unsigned int included = pallets[i - 1].get_profit() +
                                dp->get(i - 1, w - pallets[i - 1].get_weight());
        unsigned int excluded = dp->get(i - 1, w);
        unsigned int value = std::max(included, excluded);

        // Only set the value if it's non-zero (to avoid adding unnecessary
        // entries)
        if (value > 0) {
          dp->set(i, w, value);
        }
      } else {
        unsigned int value = dp->get(i - 1, w);
        // Only set the value if it's non-zero
        if (value > 0) {
          dp->set(i, w, value);
        }
      }
    }
  }

  // Extract the used pallets (same as before)
  used_pallets.clear();
  unsigned int i = n, w = max_weight;
  while (i > 0 && w > 0) {
    if (dp->get(i, w) != dp->get(i - 1, w)) {
      used_pallets.push_back(pallets[i - 1]);
      w -= pallets[i - 1].get_weight();
    }
    i--;
  }

  std::reverse(used_pallets.begin(), used_pallets.end());

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                      end_time - start_time)
                      .count();

  std::size_t memory = dp->get_memory_usage();
  std::string memory_str;
  if (memory < 1024)
    memory_str = std::to_string(memory) + " B";
  else if (memory < 1024 * 1024)
    memory_str = std::to_string(memory / 1024) + " KB";
  else
    memory_str = std::to_string(memory / (1024 * 1024)) + " MB";

  message = "[DP (" +
            std::string(type == TableType::Vector ? "Vector" : "HashMap") +
            ")] Execution time: " + std::to_string(duration) +
            " ms | Memory used: " + memory_str;

  return dp->get(n, max_weight);
}

unsigned int DynamicProgramming::dp_solve(const std::vector<Pallet>& pallets,
                                          const Truck& truck,
                                          std::string& message) {
  auto start_time = std::chrono::high_resolution_clock::now();

  unsigned int n = pallets.size();
  unsigned int W = truck.get_capacity();

  // Two rows for rolling DP
  std::vector<unsigned int> prev(W + 1, 0);
  std::vector<unsigned int> curr(W + 1, 0);

  for (unsigned int i = 1; i <= n; ++i) {
    for (unsigned int w = 0; w <= W; ++w) {
      if (pallets[i - 1].get_weight() <= w) {
        unsigned int include =
            pallets[i - 1].get_profit() + prev[w - pallets[i - 1].get_weight()];
        unsigned int exclude = prev[w];
        curr[w] = std::max(include, exclude);
      } else {
        curr[w] = prev[w];
      }
    }
    std::swap(prev, curr);
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                      end_time - start_time)
                      .count();

  // Memory: two rows of (W+1) unsigned ints
  std::size_t memory = 2 * (W + 1) * sizeof(unsigned int);
  std::string memory_str;
  if (memory < 1024)
    memory_str = std::to_string(memory) + " B";
  else if (memory < 1024 * 1024)
    memory_str = std::to_string(memory / 1024) + " KB";
  else
    memory_str = std::to_string(memory / (1024 * 1024)) + " MB";

  message =
      "[DP (Vector - 2 Rows)] Execution time: " + std::to_string(duration) +
      " ms | Memory used: " + memory_str;

  return prev[W];  // Note: `prev` holds the last filled row after final swap
}
