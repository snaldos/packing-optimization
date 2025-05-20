# ILP (Python)

Python ILP (PuLP) is correct and flexible, but slower than C++ ILP. The choice between Python and C++ solvers depends on your preference for speed (C++) versus customizability and ease of use (Python). Both can be configured for secondary objectives, such as preferring fewer or higher-value items.

## DATASET 01–05, 07–16, 18-26

Finds optimal solutions, sometimes with different sets than C++ ILP/DP, confirming multiple optima.

## DATASET 06

Solves large, dense problems optimally. Correct and reasonably fast considering python execution times.

## DATASET 17

For very small datasets, ILP is overkill and slower than other approaches.
