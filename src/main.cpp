#include "Algorithms/BruteForce.h"
#include "Algorithms/DynamicProgramming.h"
#include "Batch/BatchStateManager.h"
#include "DataStructures/Pallet.h"
#include "DataStructures/Truck.h"

int main() {
  // std::vector<Pallet> pallets;
  // Truck truck;

  // // Initialize batch processor
  // BatchStateManager batch_state_manager(pallets, truck);
  // batch_state_manager.update_state();

  // Create some example pallets
  std::vector<Pallet> pallets = {
      Pallet("P1", 10, 60),
      Pallet("P2", 20, 100),
      Pallet("P3", 30, 120),
  };

  // Create a truck with a capacity of 50
  Truck truck(50, pallets.size());

  // Solve the knapsack problem
  BruteForce bruteForce;
  DynamicProgramming dynamicProgramming;
  std::vector<Pallet> used_pallets;
  std::string message;
  unsigned int max_profit = dynamicProgramming.dp_solve(
      pallets, truck, used_pallets, TableType::Vector, message);

  // max_profit = bruteForce.bf_solve(pallets, truck, used_pallets, message);

  // Output the results
  std::cout << "Maximum Profit: " << max_profit << "\n";
  std::cout << "Selected Pallets:\n";
  for (const auto& pallet : used_pallets) {
    std::cout << "ID: " << pallet.get_id()
              << ", Weight: " << pallet.get_weight()
              << ", Profit: " << pallet.get_profit() << "\n";
  }

  std::cout << message << "\n";

  max_profit = dynamicProgramming.dp_solve(pallets, truck, message);
  std::cout << "Maximum Profit: " << max_profit << "\n";
  std::cout << message << "\n";

  return 0;
}
