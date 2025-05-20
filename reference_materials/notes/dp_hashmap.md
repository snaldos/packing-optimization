# DP HASHMAP

The DP HashMap (top-down with memoization) is best for sparse tables—when only a small subset of weight/capacity states are actually used. It uses fewer entries than a vector table in these cases, saving memory. For some datasets, recursion/top-down can also be faster than bottom-up (vector), not just more memory efficient.

## DATASET 01, 03, 07, 10, 13, 14, 16

HashMap uses far fewer entries than the vector table, making it much less memory expensive, but is slower due to hash overhead.

## DATASET 02

Finds the optimal solution (profit 32, weight 98) with 702 entries (8 KB, 328 μs). Fewer entries than vector, but slower and more memory per entry.

## DATASET 04-05, 11, 18-25

Here, the table is not sparse—HashMap uses over half as many entries as vector, but each entry is more expensive. No advantage over vector in this scenarios.

## DATASET 06

For large, dense problems, such as this one (optimal: profit 2047, weight 2047), the HashMap approach is inefficient—requiring 6.3 million entries (71 MB) and 8.9 seconds to solve. It uses about twice as much memory as the vector table and is nearly 10 times slower. As problem size increases, the overhead of hashing becomes much more significant, offering no advantage over the DP bottom-up approach which takes almost 1/10 of the time to terminate.

## DATASET 08-09, 15

HashMap is both more memory efficient (less than half the memory of vector) and faster than DP Vector. Shows that top-down can outperform bottom-up in both time and space for some problems.

## DATASET 12, 17
Here, HashMap is 4 times faster while occupying 1/4 of the total memory for a vector table being the clear winner.
