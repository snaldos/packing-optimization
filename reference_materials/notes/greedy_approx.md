# GREEDY APPROXIMATION

Greedy sorts by profit-to-weight and fills the truck. Fastest and most memory-efficient, but not always optimal or meaningful: it may miss solutions with fewer, higher-value items if those don't have the best ratio. Multiple optimal sets may exist.

## DATASET 01–03, 05–09

Finds optimal solutions in microseconds. Sometimes produces a different set than DP/ILP.

## DATASET 04

Near-optimal (profit 158, weight 490) in 28 μs. Not always optimal for larger/complex datasets.

## DATASET 10

Fails: selects the small, low-value item due to its better profit/weight ratio. Classic greedy failure case—does not find the optimal solution.
