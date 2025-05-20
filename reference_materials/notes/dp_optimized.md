# DP OPTIMIZED (2 Rolling Rows)

The most memory-efficient DP method, using only two rows. Cannot reconstruct the set of used pallets, only the max profit. Ideal for large or memory-constrained cases.

## DATASET 01–05, 07-10

Finds the correct max profit with minimal memory and very fast execution. Cannot reconstruct used pallets.

## DATASET 06

Correct max profit (2047) with 4096 entries (16 KB, 412 ms). This is a case when using this is significantly more memory efficient going from 31MB to 16KB, an astounding difference.
