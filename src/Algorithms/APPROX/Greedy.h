#ifndef GREEDY_H
#define GREEDY_H

#include <algorithm>
#include <chrono>
#include <vector>

#include "../../DataStructures/Pallet.h"
#include "../../DataStructures/Truck.h"

/*

  - Implement the greedy algorithm studied in class that selects pallets based
  on their weight-to-profit ratio, where the last pallet might not be included
  as one cannot consider a fraction of a pallet.
  - Compare the accuracy and performance of this approximation algorithm with
  the optimal solutions obtained from the exhaustive and dynamic programming
  approaches (using only small datasets).
  - Evaluate the performance and fidelity of the greedy algorithm in the small
  and large data sets.
  - Remember that this problem is not the Fractional Knapsack Problem.

*/

class Greedy {
 public:
  unsigned int approx_solve(const std::vector<Pallet>& pallets,
                            const Truck& truck,
                            std::vector<Pallet>& used_pallets,
                            std::string& message);
};

#endif  // GREEDY_H
