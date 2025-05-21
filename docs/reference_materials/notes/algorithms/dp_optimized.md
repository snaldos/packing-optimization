# DP OPTIMIZED (2 Rolling Rows)

The most memory-efficient DP method, using only two rows. Cannot reconstruct the set of used pallets, only the max profit. Ideal for large or memory-constrained cases.

## DATASET 01–05, 07-16, 18-25

Finds the correct max profit with minimal memory and very fast execution. Cannot reconstruct used pallets.

## DATASET 06

Correct max profit (2047) with 4096 entries (16 KB, 412 ms). This is a case when using this is significantly more memory efficient going from 31MB to 16KB, an astounding difference.

## DATASET 17

For such a small dataset using this optimized approach ends up being redundant since it uses almost the same space as the normal dp vector table approach while not being able to identify the used pallets.

## DATASET 26

With a very large truck capacity (100,000), the two-row DP optimized approach still requires two rows of length 100,001, resulting in significant memory usage (781 KB) and a long execution time (150 ms). Although it is more memory efficient than the full DP vector table, the time complexity remains pseudo-polynomial, scaling with the capacity rather than the number of items. This makes it impractical for problems with large capacities, even if the number of items is small.
