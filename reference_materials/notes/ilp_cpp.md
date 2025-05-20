# ILP (CPP)

C++ ILP (OR-Tools) is robust and flexible, always finds the optimum, and can be configured to prefer more meaningful solutions (e.g., fewer, higher-value items) if secondary objectives are added. By default, it returns any optimal set.

## DATASET 01–05, 07–16

Finds optimal solutions, sometimes with different sets than DP/Greedy, confirming multiple optima.

## DATASET 06

Optimal (profit 2047, weight 2047). For large, dense problems, ILP is correct and much faster.

## DATASET 17

For very small datasets, ILP is overkill and slower than other approaches.
