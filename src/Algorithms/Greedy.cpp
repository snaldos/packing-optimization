#include "Greedy.h"

unsigned int Greedy::approx_solve(const std::vector<Pallet>& pallets,
                           const Truck& truck,
                           std::vector<Pallet>& used_pallets,
                           std::string& message) {
  auto start_time = std::chrono::high_resolution_clock::now();

  // Sort pallets by profit-to-weight ratio in descending order
  std::vector<Pallet> sorted_pallets = pallets;
  std::sort(sorted_pallets.begin(), sorted_pallets.end(),
            [](const Pallet& a, const Pallet& b) {
              return (double)a.get_profit() / a.get_weight() >
                     (double)b.get_profit() / b.get_weight();
            });

  unsigned int total_profit = 0;
  unsigned int remaining_weight = truck.get_capacity();
  used_pallets.clear();

  // Select pallets greedily
  for (const auto& pallet : sorted_pallets) {
    if (pallet.get_weight() <= remaining_weight) {
      used_pallets.push_back(pallet);
      total_profit += pallet.get_profit();
      remaining_weight -= pallet.get_weight();
    }
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                      end_time - start_time)
                      .count();

  message = "[Greedy] Execution time: " + std::to_string(duration) + " ms";

  return total_profit;
}
