# Backtracking_sudoku_solver
Sudoku solver that uses backtracking algorithm.

My first thought was to make an algorithm that always searches for an empty cell that can be filled by only one value. Filling that cell made it possible to fill another empty cell and the algorith goes till the whole gameboard is filled up. That algorithm was naive and did not work in harder cases (like test2.txt) so i made an algorithm that it able to check all possible numbers to put in a cell and then when next cell has no possible numbers, algorithm comes back and changes previous cells.

test1.txt consists simple test gameboard.
test2.txt consists harder case.
test3.txt consists empty gameboard.
