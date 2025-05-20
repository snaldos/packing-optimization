# GREEDY APPROXIMATION

Greedy sorts by profit-to-weight and fills the truck. Fastest and most memory-efficient, but not always optimal or meaningful: it may miss solutions with fewer, higher-value items if those don't have the best ratio. Multiple optimal sets may exist.

## DATASET 01–03, 05–09, 12–13, 15, 20, 23-24, 26

Finds optimal solutions in microseconds. Sometimes produces a different set than DP/ILP.

## DATASET 04, 11, 14, 18, 22, 25

Near-optimal. Not always optimal for larger/complex datasets.

## DATASET 10

Fails: selects the small, low-value item due to its better profit/weight ratio. Classic greedy failure case—does not find the optimal solution.

## DATASET 16

Classic greedy trap: greedy selects many small items and misses the single large, high-value item (far from optimal).

## DATASET 19, 21

Greedy fails by selecting small, low value, high profit/weight ration instead of using them partially to then include greater value items that were still able to fit in the truck.
