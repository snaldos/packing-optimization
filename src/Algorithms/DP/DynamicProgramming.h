#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <algorithm>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"
#include "DPTable.h"
#include "HashMapDPTable.h"
#include "VectorDPTable.h"

enum class TableType { Vector, HashMap };

class DynamicProgramming {
 private:
  std::unique_ptr<DPTable> create_table(TableType type, unsigned int n,
                                        unsigned int max_weight);

  unsigned int dp_solve_top_down(const std::vector<Pallet>& pallets,
                                 std::unique_ptr<DPTable>& dp, unsigned int i,
                                 unsigned int w);

  unsigned int dp_solve_top_down(const std::vector<Pallet>& pallets,
                                 std::unique_ptr<DPTable>& dp, unsigned int i,
                                 unsigned int w,
                                 std::vector<Pallet>& used_pallets);

  unsigned int dp_solve_bottom_up(const std::vector<Pallet>& pallets,
                                  std::unique_ptr<DPTable>& dp, unsigned int n,
                                  unsigned int max_weight,
                                  std::vector<Pallet>& used_pallets);

 public:
  unsigned int dp_solve(const std::vector<Pallet>& pallets, const Truck& truck,
                        std::vector<Pallet>& used_pallets, TableType type,
                        std::string& message);

  unsigned int dp_solve(const std::vector<Pallet>& pallets, const Truck& truck,
                        std::string& message);
};

#endif  // DYNAMICPROGRAMMING_H
