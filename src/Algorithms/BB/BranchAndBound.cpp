#include "BranchAndBound.h"
#include <algorithm>

// Upper bound using fractional knapsack (greedy estimate)
double BranchAndBound::estimate_upper_bound(const std::vector<Pallet> &pallets,
                                            unsigned int index,
                                            unsigned int curr_weight,
                                            unsigned int curr_value,
                                            unsigned int max_weight) {
    double bound = curr_value;
    unsigned int weight = curr_weight;
    for (unsigned int i = index; i < pallets.size(); ++i) {
        unsigned int w = pallets[i].get_weight();
        unsigned int p = pallets[i].get_profit();
        if (weight + w <= max_weight) {
            weight += w;
            bound += p;
        } else {
            unsigned int remaining_weight = max_weight - weight;
            bound += (double)p / w * remaining_weight;
            break;
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
                               bool &timed_out) {
    if (timed_out)
        return;
    if (std::chrono::steady_clock::now() > deadline) {
        timed_out = true;
        return;
    }
    if (curr_weight > max_weight)
        return;
    if (estimate_upper_bound(pallets, index, curr_weight, curr_value, max_weight) <= best_value)
        return;
    if (index == pallets.size()) {
        if (curr_value > best_value) {
            best_value = curr_value;
            best_used = curr_used;
        }
        return;
    }
    // Include
    curr_used[index] = true;
    bb_helper(pallets, index + 1, curr_weight + pallets[index].get_weight(),
              curr_value + pallets[index].get_profit(), max_weight, curr_used,
              best_used, best_value, deadline, timed_out);
    // Exclude
    curr_used[index] = false;
    bb_helper(pallets, index + 1, curr_weight, curr_value, max_weight, curr_used,
              best_used, best_value, deadline, timed_out);
}

unsigned int BranchAndBound::bb_solve(std::vector<Pallet> pallets,
                                      const Truck &truck,
                                      std::vector<Pallet> &used_pallets,
                                      std::string &message,
                                      unsigned int timeout_ms) {
    auto start_time = std::chrono::steady_clock::now();
    unsigned int half_timeout = timeout_ms / 2;
    bool timed_out = false;
    double max_value = 0, max_weight = 0, total_value = 0;
    for (unsigned int i = 0; i < pallets.size(); ++i) {
        double v = pallets[i].get_profit();
        double w = pallets[i].get_weight();
        total_value += v;
        if (v > max_value) {
            max_value = v;
            max_weight = w;
        }
    }
    double capacity = truck.get_capacity();
    bool value_first =
        (max_weight >= 0.8 * capacity) && (max_value >= 0.5 * total_value);
    auto sort_by_value = [](const Pallet &a, const Pallet &b) {
        return a.get_profit() > b.get_profit();
    };
    auto sort_by_ratio = [](const Pallet &a, const Pallet &b) {
        return (double)a.get_profit() / a.get_weight() >
               (double)b.get_profit() / b.get_weight();
    };
    if (value_first) {
        std::sort(pallets.begin(), pallets.end(), sort_by_value);
    } else {
        std::sort(pallets.begin(), pallets.end(), sort_by_ratio);
    }
    unsigned int n = pallets.size();
    std::vector<bool> curr_used(n, false);
    std::vector<bool> best_used(n, false);
    unsigned int best_value = 0;
    unsigned int truck_capacity = truck.get_capacity();
    auto deadline = start_time + std::chrono::milliseconds(half_timeout);
    bb_helper(pallets, 0, 0, 0, truck_capacity, curr_used, best_used, best_value,
              deadline, timed_out);
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
        if (value_first) {
            std::sort(pallets.begin(), pallets.end(), sort_by_ratio);
        } else {
            std::sort(pallets.begin(), pallets.end(), sort_by_value);
        }
        curr_used.assign(n, false);
        best_used.assign(n, false);
        best_value = 0;
        used_pallets.clear();
        timed_out = false;
        auto retry_start = std::chrono::steady_clock::now();
        auto retry_deadline = retry_start + std::chrono::milliseconds(half_timeout);
        bb_helper(pallets, 0, 0, 0, truck_capacity, curr_used, best_used,
                  best_value, retry_deadline, timed_out);
        for (unsigned int i = 0; i < n; ++i) {
            if (best_used[i]) {
                used_pallets.push_back(pallets[i]);
            }
        }
        auto retry_end = std::chrono::steady_clock::now();
        auto retry_duration = std::chrono::duration_cast<std::chrono::microseconds>(
                                  retry_end - retry_start)
                                  .count();
        if (timed_out) {
            message = "[BB] Timeout after both sort strategies (" +
                      std::to_string(timeout_ms) + " ms total).";
            used_pallets.clear();
            return 0;
        } else {
            message = "[BB] Execution time: " + std::to_string(retry_duration) +
                      " μs (used alternative sort after initial timeout)";
            return best_value;
        }
    }
    message = "[BB] Execution time: " + std::to_string(duration) + " μs";
    return best_value;
}
