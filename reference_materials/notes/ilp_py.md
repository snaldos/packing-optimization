# ILP (PYTHON)

Python ILP (PuLP) is correct but much slower than C++ ILP. Like C++ ILP, it can be configured to prefer more meaningful solutions (e.g., fewer, higher-value items) if secondary objectives are added. By default, it returns any optimal set.

## DATASET 01–05, 07–10

Finds optimal solutions, sometimes with different sets than C++ ILP/DP, confirming multiple optima.

## DATASET 06

Optimal (profit 2047, weight 2047) in 199 ms. For large, dense problems, Python ILP is correct but much slower cpp ILP.
