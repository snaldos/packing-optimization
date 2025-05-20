# BRUTE FORCE

## DATASET 01

The brute force approach checks all possible combinations and guarantees the optimal solution. For dataset 01, it finds the correct maximum profit and set of pallets, but is much slower than the DP and Greedy methods (372 μs). This method is only practical for very small datasets due to its exponential time complexity.

## DATASET 02

For dataset 02, brute force again finds the optimal solution (profit 32, total weight 98), but the execution time increases significantly (9103 μs) compared to dataset 01. This highlights the exponential growth in computation time as the problem size increases. Brute force remains impractical for larger datasets, but is still a useful baseline for small cases.

## DATASET 03

For dataset 03, brute force finds the optimal solution (profit 40, total weight 97) with an execution time of 232 μs. The method remains practical for very small datasets, but is outperformed by DP and Greedy in both speed and memory usage as the problem size grows.
