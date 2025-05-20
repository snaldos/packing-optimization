# DP VECTOR

The DP Vector (bottom-up) is ideal for small to medium, dense problems where most weight/capacity states are used. It is fast and simple, and can reconstruct a meaningful solution (e.g., with fewer, higher-value items) if such exists, since it explores all combinations.

## DATASET 01–03, 05, 07–10

Optimal, fast, and uses moderate memory (all 1-unit, high-profit pallets for 09). Remains efficient for this size.

## DATASET 04

Optimal, starting to become memory expensive.

## DATASET 06

Optimal (profit 2047, weight 2047), 8.4M entries (31 MB, 901540 μs). Memory use is very high for large, dense problems.
