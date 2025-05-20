#include "DynamicProgramming.h"

std::unique_ptr<DPTable> DynamicProgramming::create_table(
    TableType type, unsigned int n, unsigned int max_weight) {
  if (type == TableType::Vector)
    return std::make_unique<VectorDPTable>(n, max_weight);
  else
    return std::make_unique<HashMapDPTable>();
}

unsigned int DynamicProgramming::dp_solve_top_down(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int i, unsigned int w,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  if (std::chrono::steady_clock::now() > deadline) {
    timed_out = true;
    return 0;
  }
  if (i == 0 || w == 0) return 0;

  unsigned int cached = dp->get(i, w);
  if (cached != NOT_COMPUTED) return cached;

  unsigned int result;
  if (pallets[i - 1].get_weight() > w) {
    result = dp_solve_top_down(pallets, dp, i - 1, w, deadline, timed_out);
  } else {
    unsigned int included =
        pallets[i - 1].get_profit() +
        dp_solve_top_down(pallets, dp, i - 1, w - pallets[i - 1].get_weight(),
                          deadline, timed_out);
    unsigned int excluded =
        dp_solve_top_down(pallets, dp, i - 1, w, deadline, timed_out);
    result = std::max(included, excluded);
  }

  dp->set(i, w, result);
  return result;
}

unsigned int DynamicProgramming::dp_solve_top_down(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int i, unsigned int w, std::vector<Pallet> &used_pallets,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  unsigned int result =
      dp_solve_top_down(pallets, dp, i, w, deadline, timed_out);
  if (timed_out)
    return 0;
  // Backtrack for used pallets (HashMap style)
  used_pallets.clear();
  std::function<unsigned int(unsigned int, unsigned int)> get_or_compute;
  get_or_compute = [&](unsigned int i, unsigned int w) -> unsigned int {
    unsigned int v = dp->get(i, w);
    if (v != NOT_COMPUTED) return v;
    if (i == 0 || w == 0) return 0;
    if (pallets[i - 1].get_weight() > w) return get_or_compute(i - 1, w);
    unsigned int included =
        pallets[i - 1].get_profit() +
        get_or_compute(i - 1, w - pallets[i - 1].get_weight());
    unsigned int excluded = get_or_compute(i - 1, w);
    return std::max(included, excluded);
  };
  while (i > 0 && w > 0) {
    unsigned int curr = get_or_compute(i, w);
    unsigned int excl = get_or_compute(i - 1, w);
    if (curr != excl) {
      used_pallets.push_back(pallets[i - 1]);
      w -= pallets[i - 1].get_weight();
    }
    i--;
  }
  std::reverse(used_pallets.begin(), used_pallets.end());
  return result;
}

unsigned int DynamicProgramming::dp_solve_bottom_up(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int n, unsigned int max_weight, std::vector<Pallet> &used_pallets,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  for (unsigned int i = 1; i <= n; i++) {
    for (unsigned int w = 0; w <= max_weight; w++) {
      if (std::chrono::steady_clock::now() > deadline) {
        timed_out = true;
        return 0;
      }
      if (pallets[i - 1].get_weight() <= w) {
        unsigned int included = pallets[i - 1].get_profit() +
                                dp->get(i - 1, w - pallets[i - 1].get_weight());
        unsigned int excluded = dp->get(i - 1, w);
        unsigned int value = std::max(included, excluded);
        dp->set(i, w, value);
      } else {
        unsigned int value = dp->get(i - 1, w);
        dp->set(i, w, value);
      }
    }
  }
  // Backtrack for used pallets (Vector style)
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
  return dp->get(n, max_weight);
}

unsigned int DynamicProgramming::dp_solve(const std::vector<Pallet> &pallets,
                                          const Truck &truck,
                                          std::vector<Pallet> &used_pallets,
                                          TableType type, std::string &message,
                                          unsigned int timeout_ms) {
  auto start_time = std::chrono::steady_clock::now();
  auto deadline = start_time + std::chrono::milliseconds(timeout_ms);
  auto dp = create_table(type, pallets.size(), truck.get_capacity());
  unsigned int n = pallets.size();
  unsigned int max_weight = truck.get_capacity();
  unsigned int result = 0;
  bool timed_out = false;

  if (type == TableType::Vector) {
    // Use bottom-up approach
    result = dp_solve_bottom_up(pallets, dp, n, max_weight, used_pallets,
                                deadline, timed_out);
  } else {
    // Use top-down recursive with memoization for sparse table
    result = dp_solve_top_down(pallets, dp, n, max_weight, used_pallets,
                               deadline, timed_out);
  }

  auto end_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  std::size_t num_entries = dp->get_num_entries();
  std::size_t memory = dp->get_memory_usage();
  std::string memory_str;
  if (memory < 1024)
    memory_str = std::to_string(memory) + " B";
  else if (memory < 1024 * 1024)
    memory_str = std::to_string(memory / 1024) + " KB";
  else
    memory_str = std::to_string(memory / (1024 * 1024)) + " MB";

  if (timed_out) {
    message = "[DP (" +
              std::string(type == TableType::Vector ? "Vector" : "HashMap") +
              " Table)] Timeout after " + std::to_string(timeout_ms) + " ms.";
    return 0;
  }

  message = "[DP (" +
            std::string(type == TableType::Vector ? "Vector" : "HashMap") +
            " Table)] Execution time: " + std::to_string(duration) +
            " μs | Memory used for " + std::to_string(num_entries) +
            " entries: " + memory_str;

  return result;
}

unsigned int DynamicProgramming::dp_solve(const std::vector<Pallet> &pallets,
                                          const Truck &truck,
                                          std::string &message,
                                          unsigned int timeout_ms) {
  auto start_time = std::chrono::steady_clock::now();
  auto deadline = start_time + std::chrono::milliseconds(timeout_ms);

  unsigned int n = pallets.size();
  unsigned int W = truck.get_capacity();

  // Two rows for rolling DP
  std::vector<unsigned int> prev(W + 1, 0);
  std::vector<unsigned int> curr(W + 1, 0);

  for (unsigned int i = 1; i <= n; ++i) {
    for (unsigned int w = 0; w <= W; ++w) {
      if (std::chrono::steady_clock::now() > deadline) {
        message = "[DP (2 Rolling Rows)] Timeout after " +
                  std::to_string(timeout_ms) + " ms.";
        return 0;
      }
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

  auto end_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  // Memory: two rows of (W+1) unsigned ints
  std::size_t num_entries = 2 * (W + 1);
  std::size_t memory = 2 * (W + 1) * sizeof(unsigned int);
  std::string memory_str;
  if (memory < 1024)
    memory_str = std::to_string(memory) + " B";
  else if (memory < 1024 * 1024)
    memory_str = std::to_string(memory / 1024) + " KB";
  else
    memory_str = std::to_string(memory / (1024 * 1024)) + " MB";

  message =
      "[DP (2 Rolling Rows)] Execution time: " + std::to_string(duration) +
      " μs | Memory used for " + std::to_string(num_entries) +
      " entries: " + memory_str;

  return prev[W];  // Note: `prev` holds the last filled row after final swap
}
