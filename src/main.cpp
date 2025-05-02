#include "Algorithms/BruteForce.h"
#include "Algorithms/DynamicProgramming.h"
#include "Algorithms/Greedy.h"
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

  // Solve using Greedy
  Greedy greedy;
  std::vector<Pallet> used_pallets_greedy;
  std::string message_greedy;
  unsigned int max_profit_greedy =
      greedy.approx_solve(pallets, truck, used_pallets_greedy, message_greedy);

  // Solve using Brute Force
  BruteForce bruteForce;
  std::vector<Pallet> used_pallets_bf;
  std::string message_bf;
  unsigned int max_profit_bf =
      bruteForce.bf_solve(pallets, truck, used_pallets_bf, message_bf);

  // Solve using Dynamic Programming
  DynamicProgramming dynamicProgramming;
  std::vector<Pallet> used_pallets_dp;
  std::string message_dp;
  unsigned int max_profit_dp = dynamicProgramming.dp_solve(
      pallets, truck, used_pallets_dp, TableType::Vector, message_dp);

  // Output results
  std::cout << "Greedy Algorithm:\n";
  std::cout << "Maximum Profit: " << max_profit_greedy << "\n";
  std::cout << "Used Pallets: ";
  for (const auto& pallet : used_pallets_greedy) {
    std::cout << pallet.get_id() << " " << pallet.get_weight() << " "
              << pallet.get_profit() << ", ";
  }
  std::cout << "\n";
  std::cout << message_greedy << "\n";

  std::cout << "Brute Force Algorithm:\n";
  std::cout << "Maximum Profit: " << max_profit_bf << "\n";
  std::cout << "Used Pallets: ";
  for (const auto& pallet : used_pallets_bf) {
    std::cout << pallet.get_id() << " " << pallet.get_weight() << " "
              << pallet.get_profit() << ", ";
  }
  std::cout << "\n";
  std::cout << message_bf << "\n";

  std::cout << "Dynamic Programming Algorithm:\n";
  std::cout << "Maximum Profit: " << max_profit_dp << "\n";
  std::cout << "Used Pallets: ";
  for (const auto& pallet : used_pallets_dp) {
    std::cout << pallet.get_id() << " " << pallet.get_weight() << " "
              << pallet.get_profit() << ", ";
  }
  std::cout << "\n";
  std::cout << message_dp << "\n";

  return 0;

  return 0;
}
