#include "Greedy.h"

unsigned int Greedy::approx_solve(const std::vector<Pallet> &pallets,
                                  const Truck &truck,
                                  std::vector<Pallet> &used_pallets,
                                  std::string &message,
                                  unsigned int timeout_ms) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto timeout = std::chrono::milliseconds(timeout_ms);

  // Sort pallets by profit-to-weight ratio in descending order
  std::vector<Pallet> sorted_pallets = pallets;
  std::sort(
      sorted_pallets.begin(), sorted_pallets.end(),
      [](const Pallet& a, const Pallet& b) {
        double ratio_a = (double)a.get_profit() / a.get_weight();
        double ratio_b = (double)b.get_profit() / b.get_weight();
        if (ratio_a == ratio_b) {
          if (a.get_profit() == b.get_profit()) {
            return a.get_id() < b.get_id(); // Lexicographical order by ID
          }
          return a.get_profit() >
                 b.get_profit();  // Larger profits first if ratios are the same
        }
        return ratio_a > ratio_b;
      });

  unsigned int total_profit = 0;
  unsigned int remaining_weight = truck.get_capacity();
  used_pallets.clear();

  // Select pallets greedily
  for (const auto& pallet : sorted_pallets) {
    auto now = std::chrono::high_resolution_clock::now();
    if (now - start_time > timeout) {
      message = "[Greedy] Timeout: Algorithm exceeded " +
                std::to_string(timeout_ms) + " ms.";
      return 0;
    }
    if (pallet.get_weight() <= remaining_weight) {
      used_pallets.push_back(pallet);
      total_profit += pallet.get_profit();
      remaining_weight -= pallet.get_weight();
    }
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  message = "[Greedy] Execution time: " + std::to_string(duration) + " μs";

  return total_profit;
}
