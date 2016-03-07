### Summary

Solves n-queen puzzles with a non-backtracking, hill-climbing approach. Able to solve `n`<=800 under 30 seconds.

Input: `n` for `n`>=4  
Output: `n` sized board with `n` non-colliding queens, along with time taken to solve. (If `n`>=300, user is prompted whether or not to print the board.)

### Example

Input: `15`    
Output:
```
_|_|_|_|_|_|_|_|_|_|Q|_|_|_|_|
_|_|_|_|_|_|Q|_|_|_|_|_|_|_|_|
_|_|_|_|_|_|_|_|_|_|_|_|_|_|Q|
_|_|_|Q|_|_|_|_|_|_|_|_|_|_|_|
_|_|_|_|_|_|_|_|_|_|_|Q|_|_|_|
_|_|_|_|Q|_|_|_|_|_|_|_|_|_|_|
_|_|_|_|_|_|_|_|_|_|_|_|Q|_|_|
_|_|_|_|_|Q|_|_|_|_|_|_|_|_|_|
_|_|_|_|_|_|_|_|_|Q|_|_|_|_|_|
_|_|Q|_|_|_|_|_|_|_|_|_|_|_|_|
_|_|_|_|_|_|_|_|_|_|_|_|_|Q|_|
_|_|_|_|_|_|_|_|Q|_|_|_|_|_|_|
_|Q|_|_|_|_|_|_|_|_|_|_|_|_|_|
_|_|_|_|_|_|_|Q|_|_|_|_|_|_|_|
Q|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
Solved in 0.002001s
```

### How it works

A `Board` object represents the current chess board. When initialized, queens are placed starting from the top left corner diagonally towards the bottom right corner. By only swapping columns, we prevent the need to check for horizontal and vertical "collisions" (queen attacking queen), improving efficiency. Because there is only 1 queen per column, I store the value of each queen's row position with the array `int[] queen_row_pos`, and the number of collisions each queen per column with `int[] num_collisions`. For example, `queen_row_pos[0]` would give the row value of the queen at column 0, and `num_collisions[0]` would give the number of collisions that the queen at column 0 is producing.

`Board::getBadCol()` returns the column value of a queen whose collision count is greater than 0. This column is then swapped with a different random column through `Board::swapIfGood(int col1, int col2)`. If the overall collision count is reduced, the swap is kept. However, if the overall collision count is increased, the swap is reversed (except for when `rand()%10000>1`, in order to prevent being stuck on a local maximum). This process is repeated until every value in `num_collisions` is 0, at which point the solution has been found.

### `n` v. solving time (i5-5200U 2.2 ghz processor)

`n`|seconds
---:|---
4|0
10|0
20|0.002
40|0.015
60|0.010
80|0.035
100|0.065
200|0.450
300|1.981
500|6.412
800|27.71
1000|52.04
