#include "BruteForce.h"

// Simple backtracking helper (no upper bound, no sorting)
void BruteForce::bt_helper(const std::vector<Pallet> &pallets,
                           unsigned int index, unsigned int curr_weight,
                           unsigned int curr_value, unsigned int max_weight,
                           std::vector<bool> &curr_used,
                           std::vector<bool> &best_used,
                           unsigned int &best_value,
                           std::chrono::steady_clock::time_point deadline,
                           bool &timed_out) {
  if (timed_out)
    return;
  if (std::chrono::steady_clock::now() > deadline) {
    timed_out = true;
    return;
  }
  if (curr_weight > max_weight)
    return;
  if (index == pallets.size()) {
    if (curr_value > best_value) {
      best_value = curr_value;
      best_used = curr_used;
    }
    return;
  }
  // Include current pallet
  curr_used[index] = true;
  bt_helper(pallets, index + 1, curr_weight + pallets[index].get_weight(),
            curr_value + pallets[index].get_profit(), max_weight, curr_used,
            best_used, best_value, deadline, timed_out);
  // Exclude current pallet
  curr_used[index] = false;
  bt_helper(pallets, index + 1, curr_weight, curr_value, max_weight, curr_used,
            best_used, best_value, deadline, timed_out);
}

unsigned int BruteForce::bt_solve(std::vector<Pallet> pallets,
                                  const Truck &truck,
                                  std::vector<Pallet> &used_pallets,
                                  std::string &message,
                                  unsigned int timeout_ms) {
  auto start_time = std::chrono::steady_clock::now();
  bool timed_out = false;
  unsigned int n = pallets.size();
  std::vector<bool> curr_used(n, false);
  std::vector<bool> best_used(n, false);
  unsigned int best_value = 0;
  unsigned int truck_capacity = truck.get_capacity();
  auto deadline = start_time + std::chrono::milliseconds(timeout_ms);

  bt_helper(pallets, 0, 0, 0, truck_capacity, curr_used, best_used, best_value,
            deadline, timed_out);

  // Collect the used pallets
  used_pallets.clear();
  for (unsigned int i = 0; i < n; ++i) {
    if (best_used[i]) {
      used_pallets.push_back(pallets[i]);
    }
  }

  auto end_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  if (timed_out) {
    used_pallets.clear();
    message = "[BF (BT)] Timeout after " + std::to_string(timeout_ms) + " ms.";
    return 0;
  }

  message = "[BF (BT)] Execution time: " + std::to_string(duration) + " μs";
  return best_value;
}

unsigned int BruteForce::bf_solve(const std::vector<Pallet> &pallets,
                                  const Truck &truck,
                                  std::vector<Pallet> &used_pallets,
                                  std::string &message,
                                  unsigned int timeout_ms) {
  auto start_time = std::chrono::steady_clock::now();
  auto deadline = start_time + std::chrono::milliseconds(timeout_ms);
  bool timed_out = false;

  unsigned int n = pallets.size();
  unsigned int max_weight = truck.get_capacity();
  unsigned int best_value = 0;
  std::vector<Pallet> best_pallets;

  // Iterate through all possible subsets (2^n subsets)
  uint64_t total_subsets = 1ULL << n;
  for (uint64_t subset = 0; subset < total_subsets; ++subset) {
    if (std::chrono::steady_clock::now() > deadline) {
      timed_out = true;
      break;
    }
    unsigned int curr_weight = 0;
    unsigned int curr_value = 0;
    std::vector<Pallet> current_pallets;
    for (unsigned int i = 0; i < n; ++i) {
      if (subset & (1ULL << i)) {
        curr_weight += pallets[i].get_weight();
        curr_value += pallets[i].get_profit();
        current_pallets.push_back(pallets[i]);
      }
    }
    if (curr_weight <= max_weight && curr_value > best_value) {
      best_value = curr_value;
      best_pallets = current_pallets;
    }
  }

  // Store the best pallets
  used_pallets = best_pallets;

  auto end_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  if (timed_out) {
    used_pallets.clear();
    message = "[BF] Timeout after " + std::to_string(timeout_ms) + " ms.";
    return 0;
  }

  message = "[BF] Execution time: " + std::to_string(duration) + " μs";
  return best_value;
}
