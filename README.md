# Sudoku
A very simple graphical sudoku solver written in C++. For the graphical representation of the Sudoku I used the `SFML 2.5.1` library.

## Backtracking Algorithm
**Backtracking** is a class of algorithms for finding solutions to some computational problems, notably constraint satisfaction problems. This algorithm incrementally build up the solution and verifies the validity of the candidates. It immediately abandons any candidate that cannot possibly be completed to a valid solution. The backtracking algorithm can only be applied to problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution; like sudoku. Using the backtracking algorithm, we can incrementally fill the cells with numbers and at each stage, check whether the candidate can possibly lead to a valid solution. A few other problems where the backtracking algorithm is applicable are:

* Crosswords
* Verbal Arithmetic
* 8 Queen Puzzle
