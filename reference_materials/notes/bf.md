# BRUTE FORCE

Brute force checks all combinations and always finds the optimum, but is only practical for very small datasets due to exponential time.

## DATASET 01–03, 07–10, 13-14

Finds the optimal solution, but is much slower than DP/Greedy. Impractical as size grows.

## DATASET 11–12

Finds the optimal solution, but takes over a million (2^20) possible subsets—execution is very slow (over 1 second), clearly illustrating exponential complexity. Classic case where brute force is impractical.

## DATASET 04–06, 15-16

Times out after 60000 ms. Not feasible for moderate or large datasets.
