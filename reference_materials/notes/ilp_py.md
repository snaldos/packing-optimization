# ILP (PYTHON)

## DATASET 01

The Python ILP approach (using PuLP) also finds an optimal solution, with a different but valid set of pallets. The execution time is much higher than the C++ version (78954 μs), mainly due to Python overhead and process startup. This method is useful for prototyping or when using Python-based solvers, but is not recommended for performance-critical applications on small datasets.

## DATASET 02

The Python ILP approach (PuLP) also finds the optimal solution (profit 32, total weight 98), but is much slower than the C++ version (82221 μs). The results match the other exact methods, confirming the correctness of the approach. This method is best for prototyping or when using Python-based solvers.

## DATASET 03

The Python ILP approach (PuLP) finds the optimal solution (profit 40, total weight 94) with an execution time of 80246 μs. The results match the C++ ILP and greedy solutions, confirming the correctness of the approach. This method is best for prototyping or when using Python-based solvers, but is much slower than the C++ version.
