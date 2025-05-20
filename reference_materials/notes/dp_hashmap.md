# DP HASHMAP

## DATASET 01

Despite taking longer to finish than teh DP VECTOR take, the top down approach with memoisation ended up occupying almost 1/10 of the total number of entries that the vector table would require making it almost 3 times less memory expensive

## DATASET 02

The DP HashMap approach finds the optimal solution (profit 32, total weight 98) with 702 entries (8 KB) and an execution time of 328 μs. It occupies less entries than the vector table but uses more memory and is slower due to hash table overhead. This method is still practical for small to medium datasets, but the vector table is generally faster for dense problems.

## DATASET 03

For dataset 03, the DP HashMap approach finds the optimal solution (profit 40, total weight 97) with 172 entries (2 KB) and an execution time of 54 μs. It continues to use fewer entries than the vector table, but is slightly slower due to hash table overhead. The memory savings are more pronounced as the problem size grows, but for this dataset, both DP methods are efficient.
