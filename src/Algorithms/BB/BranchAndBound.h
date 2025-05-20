#pragma once
#include <vector>
#include <string>
#include <chrono>
#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"

class BranchAndBound {
public:
    unsigned int bb_solve(std::vector<Pallet> pallets,
                          const Truck &truck,
                          std::vector<Pallet> &used_pallets,
                          std::string &message,
                          unsigned int timeout_ms);
private:
    double estimate_upper_bound(const std::vector<Pallet> &pallets,
                                unsigned int index,
                                unsigned int curr_weight,
                                unsigned int curr_value,
                                unsigned int max_weight);
    void bb_helper(const std::vector<Pallet> &pallets,
                   unsigned int index, unsigned int curr_weight,
                   unsigned int curr_value, unsigned int max_weight,
                   std::vector<bool> &curr_used,
                   std::vector<bool> &best_used,
                   unsigned int &best_value,
                   std::chrono::steady_clock::time_point deadline,
                   bool &timed_out);
};
