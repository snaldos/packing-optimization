#include "DynamicProgramming.h"
#include "DPEntry.h"

std::unique_ptr<DPTable>
DynamicProgramming::create_table(TableType type, unsigned int n,
                                 unsigned int max_weight) {
  if (type == TableType::Vector)
    return std::make_unique<VectorDPTable>(n, max_weight);
  else
    return std::make_unique<HashMapDPTable>();
}

DPEntry DynamicProgramming::dp_solve_top_down(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int i, unsigned int w,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  if (std::chrono::steady_clock::now() > deadline) {
    timed_out = true;
    return DPEntry{};
  }
  if (i == 0 || w == 0)
    return DPEntry{};

  DPEntry cached = dp->get(i, w);
  if (cached.profit != NOT_COMPUTED_ENTRY.profit)
    return cached;

  const Pallet &p = pallets[i - 1];
  DPEntry result;

  if (p.get_weight() > w) {
    result = dp_solve_top_down(pallets, dp, i - 1, w, deadline, timed_out);
  } else {
    DPEntry exclude =
        dp_solve_top_down(pallets, dp, i - 1, w, deadline, timed_out);
    DPEntry include = dp_solve_top_down(pallets, dp, i - 1, w - p.get_weight(),
                                        deadline, timed_out);
    include.profit += p.get_profit();
    include.weight += p.get_weight();
    include.count += 1;
    result = std::max(include, exclude);
  }
  dp->set(i, w, result);
  return result;
}

DPEntry DynamicProgramming::dp_solve_top_down(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int i, unsigned int w, std::vector<Pallet> &used_pallets,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  DPEntry result = dp_solve_top_down(pallets, dp, i, w, deadline, timed_out);
  if (timed_out)
    return DPEntry{};
  used_pallets.clear();
  // Use get_or_compute to ensure all needed entries are available for
  // backtracking
  std::function<DPEntry(unsigned int, unsigned int)> get_or_compute =
      [&](unsigned int i, unsigned int w) -> DPEntry {
    DPEntry entry = dp->get(i, w);
    if (entry.profit != NOT_COMPUTED_ENTRY.profit)
      return entry;
    if (i == 0 || w == 0)
      return DPEntry{};
    const Pallet &p = pallets[i - 1];
    DPEntry result;
    if (p.get_weight() > w) {
      result = get_or_compute(i - 1, w);
    } else {
      DPEntry exclude = get_or_compute(i - 1, w);
      DPEntry include = get_or_compute(i - 1, w - p.get_weight());
      include.profit += p.get_profit();
      include.weight += p.get_weight();
      include.count += 1;
      result = std::max(include, exclude);
    }
    dp->set(i, w, result);
    return result;
  };
  while (i > 0 && w > 0) {
    DPEntry curr = get_or_compute(i, w);
    const Pallet &p = pallets[i - 1];
    if (p.get_weight() <= w) {
      DPEntry incl = get_or_compute(i - 1, w - p.get_weight());
      // Only include if including this pallet actually produces curr
      if (curr.profit == incl.profit + p.get_profit() &&
          curr.weight == incl.weight + p.get_weight() &&
          curr.count == incl.count + 1) {
        used_pallets.push_back(p);
        w -= p.get_weight();
        i--;
        continue;
      }
    }
    i--;
  }
  std::reverse(used_pallets.begin(), used_pallets.end());
  return result;
}

DPEntry DynamicProgramming::dp_solve_bottom_up(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int n, unsigned int max_weight, std::vector<Pallet> &used_pallets,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  for (unsigned int i = 1; i <= n; i++) {
    for (unsigned int w = 0; w <= max_weight; w++) {
      if (std::chrono::steady_clock::now() > deadline) {
        timed_out = true;
        return DPEntry{};
      }
      const Pallet &p = pallets[i - 1];
      DPEntry exclude = dp->get(i - 1, w);
      DPEntry best = exclude;
      if (p.get_weight() <= w) {
        DPEntry include = dp->get(i - 1, w - p.get_weight());
        include.profit += p.get_profit();
        include.weight += p.get_weight();
        include.count += 1;
        if (exclude < include)
          best = include;
      }
      dp->set(i, w, best);
    }
  }
  used_pallets.clear();
  unsigned int i = n, w = max_weight;
  while (i > 0 && w > 0) {
    DPEntry curr = dp->get(i, w);
    const Pallet &p = pallets[i - 1];
    if (p.get_weight() <= w) {
      DPEntry incl = dp->get(i - 1, w - p.get_weight());
      // Only include if including this pallet actually produces curr
      if (curr.profit == incl.profit + p.get_profit() &&
          curr.weight == incl.weight + p.get_weight() &&
          curr.count == incl.count + 1) {
        used_pallets.push_back(p);
        w -= p.get_weight();
        i--;
        continue;
      }
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
  bool timed_out = false;
  DPEntry result;
  if (type == TableType::Vector) {
    result = dp_solve_bottom_up(pallets, dp, n, max_weight, used_pallets,
                                deadline, timed_out);
  } else {
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

  return result.profit;
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

  return prev[W]; // Note: `prev` holds the last filled row after final swap
}
