# GREEDY APPROXIMATION

## DATASET 01

The greedy algorithm sorts pallets by profit-to-weight ratio and selects them until the truck is full. For dataset 01, it finds an optimal solution (maximum profit 29), but the set of pallets differs from the DP/Brute Force solution. This shows that the greedy approach can be optimal for some instances, but this is not guaranteed for all datasets. It is the fastest method (11 μs) and uses minimal memory.

## DATASET 02

The greedy algorithm finds the optimal profit (32, total weight 98) and the same set of pallets as the exact methods. This shows that for dataset 02, the greedy approach is effective. It remains the fastest method (27 μs) and is suitable for quick approximations, though optimality is not guaranteed for all datasets.

## DATASET 03

The greedy algorithm finds the optimal profit (40, total weight 94) and a valid set of pallets, but the combination differs from the DP/ILP solution. It remains the fastest method (5 μs) and is suitable for quick approximations, though optimality is not guaranteed for all datasets. In this case, it finds an optimal profit but with a different set of items.
