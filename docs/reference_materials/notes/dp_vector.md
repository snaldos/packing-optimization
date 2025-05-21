# DP VECTOR

The DP Vector (bottom-up) is ideal for small to medium, dense problems where most weight/capacity states are used. It is fast and simple, and can reconstruct a meaningful solution (e.g., with fewer, higher-value items) if such exists, since it explores all combinations.

## DATASET 01–03, 05, 07–20, 22

Optimal, fast, and uses moderate memory for this size.

## DATASET 04, 21, 23-25

Optimal, starting to become memory expensive.

## DATASET 06

Optimal (profit 2047, weight 2047), 8.4M entries (31 MB, 901540 μs). Memory use is very high for large, dense problems.

## DATASET 26

For this dataset, DP Vector performs extremely poorly. The memory usage is massive (over 11 MB for just 30 items) and the execution time is very high (over 320 ms), despite the small number of pallets. This is because the DP table size is proportional to the truck's capacity (100,000), making the approach highly inefficient for large capacities, even with few items. In such cases, DP Vector is not recommended at all, as it is outperformed by other methods in both speed and memory usage.
