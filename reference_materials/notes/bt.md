# BACKTRACKING (BF-BT)

Backtracking (branch and bound) prunes the search space and is much faster than brute force, always finding the optimum. However, it may return any optimal set—including those with many small items—so the solution is not always the most meaningful in real-world contexts where, for example, fewer high-value items are preferred. Multiple optimal sets may exist.

## DATASET 01–03, 07–15

Finds optimal solutions in microseconds, often with different sets than DP/Greedy, showing multiple optima.

## DATASET 16

Timeout after 60000 ms. This dataset is a 'trap' for both greedy (which fails badly) and backtracking. Backtracking is slow here because the optimal solution is a single large item, but the search space is dominated by many small items with similar profit/weight ratios. Pruning is ineffective, so backtracking explores too many branches before finding the best one, leading to a timeout.

## DATASET 04–06

Finds an optimal solution, but for large datasets (like 06) the solution may not be practical or meaningful (e.g., filling with 1-unit items). Still much faster than brute force, but not recommended for very large or dense problems.
