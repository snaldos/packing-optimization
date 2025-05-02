#include "BruteForce.h"

// Upper bound using fractional knapsack (greedy estimate)
double BruteForce::estimate_upper_bound(const std::vector<Pallet>& pallets,
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
      unsigned int remaining = max_weight - weight;
      bound += (double)p / w * remaining;
      break;
    }
  }

  return bound;
}

void BruteForce::bt_helper(const std::vector<Pallet>& pallets,
                           unsigned int index, unsigned int curr_weight,
                           unsigned int curr_value, unsigned int max_weight,
                           std::vector<bool>& curr_used,
                           std::vector<bool>& best_used,
                           unsigned int& best_value) {
  if (curr_weight > max_weight) return;

  // Upper bound pruning
  if (estimate_upper_bound(pallets, index, curr_weight, curr_value,
                           max_weight) <= best_value)
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
  bt_helper(pallets, index + 1, curr_weight + pallets[index].get_weight(),
            curr_value + pallets[index].get_profit(), max_weight, curr_used,
            best_used, best_value);

  // Exclude
  curr_used[index] = false;
  bt_helper(pallets, index + 1, curr_weight, curr_value, max_weight, curr_used,
            best_used, best_value);
}

unsigned int BruteForce::bt_solve(std::vector<Pallet> pallets,
                                  const Truck& truck,
                                  std::vector<Pallet>& used_pallets) {
  // Sort by value-to-weight ratio descending
  std::sort(pallets.begin(), pallets.end(),
            [](const Pallet& a, const Pallet& b) {
              return (double)a.get_profit() / a.get_weight() >
                     (double)b.get_profit() / b.get_weight();
            });

  unsigned int n = pallets.size();
  std::vector<bool> curr_used(n, false);
  std::vector<bool> best_used(n, false);
  unsigned int best_value = 0;
  unsigned int max_weight = truck.get_capacity();

  bt_helper(pallets, 0, 0, 0, max_weight, curr_used, best_used, best_value);

  // Collect the used pallets
  used_pallets.clear();
  for (unsigned int i = 0; i < n; ++i) {
    if (best_used[i]) {
      used_pallets.push_back(pallets[i]);
    }
  }

  return best_value;
}

unsigned int BruteForce::bf_solve(const std::vector<Pallet>& pallets,
                                  const Truck& truck,
                                  std::vector<Pallet>& used_pallets) {
  unsigned int n = pallets.size();
  unsigned int max_weight = truck.get_capacity();
  unsigned int best_value = 0;
  std::vector<Pallet> best_pallets;

  // Iterate through all possible subsets (2^n subsets)
  unsigned int total_subsets = 1 << n;
  for (unsigned int subset = 0; subset < total_subsets; ++subset) {
    unsigned int curr_weight = 0;
    unsigned int curr_value = 0;
    std::vector<Pallet> current_pallets;

    // Check each pallet in the subset
    for (unsigned int i = 0; i < n; ++i) {
      // If the i-th bit is set
      if (subset & (1 << i)) {
        curr_weight += pallets[i].get_weight();
        curr_value += pallets[i].get_profit();
        current_pallets.push_back(pallets[i]);
      }
    }

    // Update the best solution if valid and better
    if (curr_weight <= max_weight && curr_value > best_value) {
      best_value = curr_value;
      best_pallets = current_pallets;
    }
  }

  // Store the best pallets
  used_pallets = best_pallets;
  return best_value;
}
