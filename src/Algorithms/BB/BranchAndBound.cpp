#include "BranchAndBound.h"

// Greedy upper bound estimation using fractional knapsack
double BranchAndBound::estimate_upper_bound(const std::vector<Pallet> &pallets,
                                            unsigned int index,
                                            unsigned int curr_weight,
                                            unsigned int curr_value,
                                            unsigned int max_weight,
                                            bool force_ratio_sort) {
  double bound = curr_value;
  unsigned int weight = curr_weight;

  if (force_ratio_sort) {
    std::vector<const Pallet *> remaining;
    remaining.reserve(pallets.size() - index);
    for (unsigned int i = index; i < pallets.size(); ++i)
      remaining.push_back(&pallets[i]);

    std::sort(remaining.begin(), remaining.end(),
              [](const Pallet *a, const Pallet *b) {
                return (double)a->get_profit() / a->get_weight() >
                       (double)b->get_profit() / b->get_weight();
              });

    for (const auto &p : remaining) {
      if (weight + p->get_weight() <= max_weight) {
        weight += p->get_weight();
        bound += p->get_profit();
      } else {
        unsigned int remaining_capacity = max_weight - weight;
        bound += (double)p->get_profit() / p->get_weight() * remaining_capacity;
        break;
      }
    }
  } else {
    for (unsigned int i = index; i < pallets.size(); ++i) {
      const auto &p = pallets[i];
      if (weight + p.get_weight() <= max_weight) {
        weight += p.get_weight();
        bound += p.get_profit();
      } else {
        unsigned int remaining_capacity = max_weight - weight;
        bound += (double)p.get_profit() / p.get_weight() * remaining_capacity;
        break;
      }
    }
  }

  return bound;
}

void BranchAndBound::bb_helper(const std::vector<Pallet> &pallets,
                               unsigned int index, unsigned int curr_weight,
                               unsigned int curr_value, unsigned int max_weight,
                               std::vector<bool> &curr_used,
                               std::vector<bool> &best_used,
                               unsigned int &best_value,
                               std::chrono::steady_clock::time_point deadline,
                               bool &timed_out, bool force_ratio_sort) {
  if (timed_out || std::chrono::steady_clock::now() > deadline) {
    timed_out = true;
    return;
  }

  if (curr_weight > max_weight)
    return;

  if (index >= pallets.size()) {
    if (curr_value > best_value) {
      best_value = curr_value;
      best_used = curr_used;
    }
    return;
  }

  if (force_ratio_sort &&
      curr_weight + pallets[index].get_weight() > max_weight) {
    bool all_heavier = std::all_of(
        pallets.begin() + index + 1, pallets.end(), [&](const Pallet &p) {
          return p.get_weight() >= pallets[index].get_weight();
        });
    if (all_heavier)
      return;
  }

  if (estimate_upper_bound(pallets, index, curr_weight, curr_value, max_weight,
                           force_ratio_sort) <= best_value)
    return;

  // Include current pallet
  curr_used[index] = true;
  bb_helper(pallets, index + 1, curr_weight + pallets[index].get_weight(),
            curr_value + pallets[index].get_profit(), max_weight, curr_used,
            best_used, best_value, deadline, timed_out, force_ratio_sort);

  // Exclude current pallet
  curr_used[index] = false;
  bb_helper(pallets, index + 1, curr_weight, curr_value, max_weight, curr_used,
            best_used, best_value, deadline, timed_out, force_ratio_sort);
}

unsigned int BranchAndBound::bb_solve(std::vector<Pallet> pallets,
                                      const Truck &truck,
                                      std::vector<Pallet> &used_pallets,
                                      std::string &message,
                                      unsigned int timeout_ms) {
  auto start_time = std::chrono::steady_clock::now();
  auto half_timeout = timeout_ms / 2;
  auto truck_capacity = truck.get_capacity();
  bool timed_out = false;

  // Analyze pallet set
  double total_value = 0, max_value = 0;
  unsigned int max_weight = 0;
  for (const auto &p : pallets) {
    total_value += p.get_profit();
    if (p.get_profit() > max_value) {
      max_value = p.get_profit();
      max_weight = p.get_weight();
    }
  }

  bool value_first =
      (max_weight >= 0.8 * truck_capacity) && (max_value >= 0.5 * total_value);

  auto sort_by_value = [](const Pallet &a, const Pallet &b) {
    return a.get_profit() > b.get_profit();
  };
  auto sort_by_ratio = [](const Pallet &a, const Pallet &b) {
    return (double)a.get_profit() / a.get_weight() >
           (double)b.get_profit() / b.get_weight();
  };

  std::string sort_method = value_first ? "value" : "ratio";
  std::sort(pallets.begin(), pallets.end(),
            value_first ? sort_by_value : sort_by_ratio);

  unsigned int n = pallets.size();
  std::vector<bool> curr_used(n, false), best_used(n, false);
  unsigned int best_value = 0;

  // Initial greedy solution for pruning
  unsigned int greedy_value = 0, greedy_weight = 0;
  std::vector<bool> greedy_used(n, false);
  for (unsigned int i = 0; i < n; ++i) {
    if (greedy_weight + pallets[i].get_weight() <= truck_capacity) {
      greedy_weight += pallets[i].get_weight();
      greedy_value += pallets[i].get_profit();
      greedy_used[i] = true;
    }
  }
  if (greedy_value > best_value) {
    best_value = greedy_value;
    best_used = greedy_used;
  }

  auto deadline = start_time + std::chrono::milliseconds(half_timeout);
  bool force_ratio_sort = value_first;

  bb_helper(pallets, 0, 0, 0, truck_capacity, curr_used, best_used, best_value,
            deadline, timed_out, force_ratio_sort);

  used_pallets.clear();
  for (unsigned int i = 0; i < n; ++i)
    if (best_used[i])
      used_pallets.push_back(pallets[i]);

  auto end_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  if (!timed_out) {
    message = "[BB] Execution time: " + std::to_string(duration) +
              " μs (sort: " + sort_method + ")";
    return best_value;
  }

  // Retry with alternative sorting
  std::string alt_sort_method = value_first ? "ratio" : "value";
  std::sort(pallets.begin(), pallets.end(),
            value_first ? sort_by_ratio : sort_by_value);

  curr_used.assign(n, false);
  best_used.assign(n, false);
  best_value = 0;
  used_pallets.clear();
  timed_out = false;

  auto retry_start = std::chrono::steady_clock::now();
  auto retry_deadline = retry_start + std::chrono::milliseconds(half_timeout);
  force_ratio_sort = !value_first;

  bb_helper(pallets, 0, 0, 0, truck_capacity, curr_used, best_used, best_value,
            retry_deadline, timed_out, force_ratio_sort);

  for (unsigned int i = 0; i < n; ++i)
    if (best_used[i])
      used_pallets.push_back(pallets[i]);

  auto retry_end = std::chrono::steady_clock::now();
  auto retry_duration = std::chrono::duration_cast<std::chrono::microseconds>(
                            retry_end - retry_start)
                            .count();

  if (timed_out) {
    message = "[BB] Timeout after both sort strategies (" +
              std::to_string(timeout_ms) +
              " ms total). Initial sort: " + sort_method +
              ", alternative sort: " + alt_sort_method + ".";
    used_pallets.clear();
    return 0;
  }

  message = "[BB] Execution time: " + std::to_string(retry_duration) +
            " μs (used alternative sort: " + alt_sort_method +
            ", initial sort: " + sort_method + ")";
  return best_value;
}
