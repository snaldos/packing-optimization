# BACKTRACKING (BF-BT)

## DATASET 01

The backtracking (branch and bound) approach is much faster than pure brute force (14 μs vs 372 μs) and still finds an optimal solution. It explores the solution space more efficiently by pruning branches that cannot improve the result. The set of pallets found is different from the DP/Brute Force solution, but the total profit is the same, showing that multiple optimal solutions exist for this dataset.

## DATASET 02

Backtracking (branch and bound) remains extremely fast (12 μs) and finds the optimal solution (profit 32, total weight 98). The set of pallets is the same as brute force and DP, confirming the uniqueness of the optimal solution for this dataset. This method is highly efficient for small to medium datasets.

## DATASET 03

Backtracking (branch and bound) is extremely fast (9 μs) and finds an optimal solution (profit 40, total weight 94). The set of pallets is different from the DP/Brute Force solution, confirming that multiple optimal solutions exist for this dataset. This method is highly efficient for small to medium datasets.
