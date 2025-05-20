# ILP (CPP)

## DATASET 01

The C++ ILP approach using Google OR-Tools finds an optimal solution, matching the maximum profit of 29. The set of pallets selected is different from the DP/Brute Force solution, but still optimal, confirming that multiple solutions exist. The execution time is higher than DP and Greedy (5165 μs), but still practical for small datasets. This method is more flexible for complex constraints but is overkill for small knapsack problems.

## DATASET 02

The C++ ILP approach (OR-Tools) finds the optimal solution (profit 32, total weight 98) with an execution time of 5694 μs. It matches the results of the DP and brute force methods. The ILP approach is robust and flexible, but slower than DP and Greedy for small datasets.

## DATASET 03

The C++ ILP approach (OR-Tools) finds the optimal solution (profit 40, total weight 94) with an execution time of 3541 μs. The set of pallets matches the greedy solution, showing that multiple optimal solutions exist for this dataset. The ILP approach remains robust and flexible, but is slower than DP and Greedy for small datasets.
