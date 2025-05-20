# BACKTRACKING (BF-BT)

Backtracking (branch and bound) prunes the search space and is much faster than brute force, always finding the optimum. However, it may return any optimal set—including those with many small items—so the solution is not always the most meaningful in real-world contexts where, for example, fewer high-value items are preferred. Multiple optimal sets may exist.

## DATASET 01–03, 07–15

Finds optimal solutions in microseconds, often with different sets than DP/Greedy, showing multiple optima.

## DATASET 04–06

Finds an optimal solution, but for large datasets (like 06) the solution may not be practical or meaningful (e.g., filling with 1-unit items). Still much faster than brute force, but not recommended for very large or dense problems.

## DATASET 16

This dataset traps approach where the pallets are sorted by value to weight ratio. Thanks to the heuristic, BT chooses to first try sorting by value and because of that, works wonders executing in microseconds what could take minutes or more.
