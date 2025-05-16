#include "IntegerLinearProgramming.h"

unsigned int IntegerLinearProgramming::solve_ilp_cpp(
    const std::vector<Pallet>& pallets, const Truck& truck,
    std::vector<Pallet>& used_pallets, std::string& message) {
  auto start_time = std::chrono::high_resolution_clock::now();
  unsigned int n = pallets.size();
  unsigned int max_weight = truck.get_capacity();
  unsigned int result = 0;

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();

  message = "[ILP-CPP] Execution time: " + std::to_string(duration) + " μs";
  return result;
}
