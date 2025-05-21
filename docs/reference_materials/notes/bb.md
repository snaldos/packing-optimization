# BACKTRACKING (BF-BT)

Backtracking (branch and bound) prunes the search space and is much faster than brute force, always finding the optimum. However, it may return any optimal set—including those with many small items—so the solution is not always the most meaningful in real-world contexts where, for example, fewer high-value items are preferred. Multiple optimal sets may exist.

## DATASET 01–03, 07–15, 17-18, 20, 22-24, 26

Finds optimal solutions in microseconds, often with different sets than DP/ILP, showing multiple optima.

## DATASET 04–06

Finds an optimal solution, but for large datasets (like 06) the solution may not be practical or meaningful (e.g., filling with 1-unit items). Still much faster than brute force, but not recommended for very large or dense problems.

## DATASET 16

This dataset traps approaches where the pallets are sorted by value to weight ratio. Thanks to the heuristic, BT chooses to first try sorting by value and because of that, works wonders executing in microseconds what could have taken minutes or more.

## DATASET 19, 21

This dataset traps approaches where the pallets are sorted by value to weight ratio. It also is formulated in a way that avoids the heuristic magic so it takes a while and then sorts by value, finishing rather quickly.

## DATASET 25

This dataset finally finds a way to trap in time the clever backtrack and put an end to its winning streak, leaving execution after 1 minute of trying.
It traps both approaches where the pallets are sorted by value to weight ratio and approaches where the pallets are sorted by value.

**Why does the clever backtrack still fail to solve this in under a minute?**

- The dataset contains many items with very similar value/weight ratios (e.g., 40x(10,20), 40x(11,21), 40x(23,43)), so sorting by value or ratio does not help to quickly find or prune the optimal solution.
- There are many ambiguous choices: the optimal solution requires mixing different types of items, and there are a huge number of combinations that are close in value.
- The upper bound (fractional knapsack) is not tight enough to prune most branches, because the remaining items always "look" promising, so the algorithm must explore deep into the search tree.
- "Trap" items (like the 23,43 pallets) appear attractive but block the optimal solution if included in the wrong combination, forcing the algorithm to check many suboptimal branches before backtracking.
- As a result, the search space remains enormous, and even with all the clever pruning and sorting, the algorithm cannot finish in under a minute for this instance.
