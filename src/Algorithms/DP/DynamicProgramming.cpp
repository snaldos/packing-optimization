#include "DynamicProgramming.h"
#include "DPEntry.h"

std::unique_ptr<DPTable>
DynamicProgramming::create_table(TableType type, unsigned int n,
                                 unsigned int max_weight) {
  // Use explicit return type for lambda to avoid deduction issues
  std::function<std::unique_ptr<DPEntryBase>()> entry_factory;
  if (!draw_condition)
    entry_factory = []() { return std::make_unique<DPSimpleEntry>(0); };
  else if (!lexicographical_order)
    entry_factory = []() { return std::make_unique<DPEntryDraw>(0, 0, 0); };
  else
    entry_factory = []() {
      return std::make_unique<DPEntryLex>(0, 0, 0, std::vector<std::string>{});
    };

  if (type == TableType::Vector)
    return std::make_unique<VectorDPTable>(n, max_weight, entry_factory);
  else
    return std::make_unique<HashMapDPTable>(entry_factory);
}

// Helper: create a new DPEntryBase for the include case
static std::unique_ptr<DPEntryBase>
make_include_entry(const DPEntryBase &base, const Pallet &p,
                   bool draw_condition, bool lexicographical_order) {
  if (!draw_condition) {
    return std::make_unique<DPSimpleEntry>(base.get_profit() + p.get_profit());
  } else if (!lexicographical_order) {
    return std::make_unique<DPEntryDraw>(base.get_profit() + p.get_profit(),
                                         base.get_weight() + p.get_weight(),
                                         base.get_count() + 1);
  } else {
    std::vector<std::string> ids = base.get_ids();
    ids.push_back(p.get_id());
    return std::make_unique<DPEntryLex>(base.get_profit() + p.get_profit(),
                                        base.get_weight() + p.get_weight(),
                                        base.get_count() + 1, ids);
  }
}

// --- Polymorphic Top-Down DP (no reconstruction) ---
std::unique_ptr<DPEntryBase> DynamicProgramming::dp_solve_top_down(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int i, unsigned int w,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  if (std::chrono::steady_clock::now() > deadline) {
    timed_out = true;
    return DPEntryBase::make_not_computed(draw_condition,
                                          lexicographical_order);
  }
  if (i == 0 || w == 0)
    return DPEntryBase::make_empty(draw_condition, lexicographical_order);

  const DPEntryBase &cached = dp->get(i, w);
  // NOT_COMPUTED sentinel: profit == UINT_MAX
  if (cached.get_profit() != UINT_MAX)
    return cached.clone();

  const Pallet &p = pallets[i - 1];
  std::unique_ptr<DPEntryBase> exclude =
      dp_solve_top_down(pallets, dp, i - 1, w, deadline, timed_out);
  std::unique_ptr<DPEntryBase> include;
  if (p.get_weight() <= w) {
    auto base = dp_solve_top_down(pallets, dp, i - 1, w - p.get_weight(),
                                  deadline, timed_out);
    include =
        make_include_entry(*base, p, draw_condition, lexicographical_order);
  } else {
    include = DPEntryBase::make_empty(draw_condition, lexicographical_order);
  }
  std::unique_ptr<DPEntryBase> result;
  if (*exclude < *include)
    result = std::move(include);
  else
    result = std::move(exclude);
  dp->set(i, w, result->clone());
  return result;
}

// --- Polymorphic Top-Down DP (with reconstruction) ---
std::unique_ptr<DPEntryBase> DynamicProgramming::dp_solve_top_down(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int i, unsigned int w, std::vector<Pallet> &used_pallets,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  auto result = dp_solve_top_down(pallets, dp, i, w, deadline, timed_out);
  if (timed_out)
    return DPEntryBase::make_not_computed(draw_condition,
                                          lexicographical_order);
  used_pallets.clear();
  // get_or_compute lambda for safe backtracking
  std::function<const DPEntryBase &(unsigned int, unsigned int)>
      get_or_compute =
          [&](unsigned int i, unsigned int w) -> const DPEntryBase & {
    const DPEntryBase &entry = dp->get(i, w);
    if (entry.get_profit() != UINT_MAX)
      return entry;
    if (i == 0 || w == 0) {
      auto empty =
          DPEntryBase::make_empty(draw_condition, lexicographical_order);
      dp->set(i, w, empty->clone());
      return dp->get(i, w);
    }
    const Pallet &p = pallets[i - 1];
    std::unique_ptr<DPEntryBase> exclude = get_or_compute(i - 1, w).clone();
    std::unique_ptr<DPEntryBase> include;
    if (p.get_weight() <= w) {
      auto base = get_or_compute(i - 1, w - p.get_weight()).clone();
      include =
          make_include_entry(*base, p, draw_condition, lexicographical_order);
    } else {
      include = DPEntryBase::make_empty(draw_condition, lexicographical_order);
    }
    std::unique_ptr<DPEntryBase> result;
    if (*exclude < *include)
      result = std::move(include);
    else
      result = std::move(exclude);
    dp->set(i, w, result->clone());
    return dp->get(i, w);
  };
  // Backtrack to reconstruct solution
  while (i > 0 && w > 0) {
    const DPEntryBase &curr = get_or_compute(i, w);
    const Pallet &p = pallets[i - 1];
    if (p.get_weight() <= w) {
      const DPEntryBase &incl = get_or_compute(i - 1, w - p.get_weight());
      std::unique_ptr<DPEntryBase> incl_plus =
          make_include_entry(incl, p, draw_condition, lexicographical_order);
      if (curr.equals(*incl_plus)) {
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

// --- Polymorphic Bottom-Up DP (with reconstruction) ---
std::unique_ptr<DPEntryBase> DynamicProgramming::dp_solve_bottom_up(
    const std::vector<Pallet> &pallets, std::unique_ptr<DPTable> &dp,
    unsigned int n, unsigned int max_weight, std::vector<Pallet> &used_pallets,
    std::chrono::steady_clock::time_point deadline, bool &timed_out) {
  for (unsigned int i = 1; i <= n; i++) {
    for (unsigned int w = 0; w <= max_weight; w++) {
      if (std::chrono::steady_clock::now() > deadline) {
        timed_out = true;
        return DPEntryBase::make_not_computed(draw_condition,
                                              lexicographical_order);
      }
      const Pallet &p = pallets[i - 1];
      const DPEntryBase &exclude = dp->get(i - 1, w);
      std::unique_ptr<DPEntryBase> include;
      if (p.get_weight() <= w) {
        const DPEntryBase &base = dp->get(i - 1, w - p.get_weight());
        include =
            make_include_entry(base, p, draw_condition, lexicographical_order);
      } else {
        include =
            DPEntryBase::make_empty(draw_condition, lexicographical_order);
      }
      std::unique_ptr<DPEntryBase> best;
      if (exclude < *include)
        best = std::move(include);
      else
        best = exclude.clone();
      dp->set(i, w, best->clone());
    }
  }
  used_pallets.clear();
  unsigned int i = n, w = max_weight;
  while (i > 0 && w > 0) {
    const DPEntryBase &curr = dp->get(i, w);
    const Pallet &p = pallets[i - 1];
    if (p.get_weight() <= w) {
      const DPEntryBase &incl = dp->get(i - 1, w - p.get_weight());
      std::unique_ptr<DPEntryBase> incl_plus =
          make_include_entry(incl, p, draw_condition, lexicographical_order);
      if (curr.equals(*incl_plus)) {
        used_pallets.push_back(p);
        w -= p.get_weight();
        i--;
        continue;
      }
    }
    i--;
  }
  std::reverse(used_pallets.begin(), used_pallets.end());
  return dp->get(n, max_weight).clone();
}

// --- Dispatcher: always uses polymorphic interface ---
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
  std::unique_ptr<DPEntryBase> result;
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
              " entries: " + memory_str +
              (lexicographical_order ? " | Lexicographical tie-breaking: ON"
                                     : " | Lexicographical tie-breaking: OFF");
    return result->get_profit();
}

// --- Legacy 2-row DP (kept for reference, not polymorphic) ---
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
