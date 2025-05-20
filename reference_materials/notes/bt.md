# BACKTRACK (Brute Force Backtracking)

Backtracking (brute force backtracking) is a complete search method that explores all possible combinations of items, but prunes branches early if they exceed the weight limit. Unlike brute force, which checks every subset, backtracking avoids unnecessary work by abandoning partial solutions that cannot possibly lead to a valid answer. This makes it significantly faster than pure brute force, especially for moderate-sized datasets.

## DATASET 01–03, 07–10, 13–14, 17
- Finds optimal solutions quickly (microseconds to milliseconds), much faster than brute force.
- For very small datasets, backtracking is as fast as any method.

## DATASET 04–05, 11-12
, 11–12
For moderate datasets (e.g., 11–12), backtracking is still much faster than brute force, but can take over a second due to the exponential number of possibilities.


## DATASET 06, 15-16, 18-25
For large or dense datasets (e.g., 06, 15–16, 18–25), backtracking times out (after 60 seconds) **becoming** impractical, though it still prunes many branches compared to brute force.
