#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"

/*

- Implement a brute-force algorithm that explores all possible subsets of
pallets to find the optimal solution.
- Analyze the performance of this approach and observe its limitations,
particularly for larger datasets.
- Optionally, implement a backtracking algorithmic approach to the 0/1 KP and to
try to improve efficiency

*/

class BruteForce {
 public:
  // Solves the knapsack problem using brute force (backtracking)
  unsigned int bt_solve(std::vector<Pallet> pallets, const Truck& truck,
                        std::vector<Pallet>& used_pallets,
                        std::string& message);

  // Solves the knapsack problem using brute force (explicit subset generation)
  unsigned int bf_solve(const std::vector<Pallet>& pallets, const Truck& truck,
                        std::vector<Pallet>& used_pallets,
                        std::string& message);

 private:
  // Helper function for recursive brute force
  void bt_helper(const std::vector<Pallet>& pallets, unsigned int index,
                 unsigned int curr_weight, unsigned int curr_value,
                 unsigned int max_weight, std::vector<bool>& curr_used,
                 std::vector<bool>& best_used, unsigned int& best_value);

  double estimate_upper_bound(const std::vector<Pallet>& pallets,
                              unsigned int index, unsigned int curr_weight,
                              unsigned int curr_value, unsigned int max_weight);
};

#endif  // BRUTE_FORCE_H
