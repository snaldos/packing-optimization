# DP VECTOR

## DATASET 01

The bottom-up DP approach using a vector table is very fast and provides the optimal solution. It uses a full table, which results in higher memory usage (1010 entries, 3 KB) compared to the HashMap approach, but the access is faster and the execution time is lower. This method is ideal for small to medium datasets where memory is not a constraint and backtracking is required.

## DATASET 02

The DP Vector approach again finds the optimal solution (profit 32, total weight 98) with 1515 entries (5 KB) and an execution time of 59 μs. It is faster than the HashMap approach and uses more memory, but remains efficient for this dataset size. The vector table is a good choice for problems where memory is not a constraint and fast access is needed.

## DATASET 03

The DP Vector approach again finds the optimal solution (profit 40, total weight 97) with 1010 entries (3 KB) and an execution time of 48 μs. It remains faster than the HashMap approach and is well-suited for this dataset size. The vector table is efficient for problems where memory is not a constraint and fast access is needed.
