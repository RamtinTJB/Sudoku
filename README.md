# Graphical Sudoku Solver
A very simple graphical sudoku solver written in C++. For the graphical representation of the Sudoku I used the `SFML 2.5.1` library.

<p align="center">
    <img src="/img/SudokuSolver.gif">
</p>

## Backtracking Algorithm
**Backtracking** is a class of algorithms for finding solutions to some computational problems, notably constraint satisfaction problems. This algorithm incrementally build up the solution and verifies the validity of the candidates. It immediately abandons any candidate that cannot possibly be completed to a valid solution. The backtracking algorithm can only be applied to problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution; like sudoku. Using the backtracking algorithm, we can incrementally fill the cells with numbers and at each stage, check whether the candidate can possibly lead to a valid solution. A few other problems where the backtracking algorithm is applicable to are:

* Crosswords
* Verbal Arithmetic
* 8 Queen Puzzle

The implementation of the actual backtracking algorithm is remarkably simple once the right data structures and methods are in-place. Below is a sample implementation in C++:

```cpp
bool solve(board& brd) {
    std::vector<cell> empty_cells = brd.get_all_empty_cells();

    // No empty cells means the Sudoku has been solved
    if (empty_cells.empty())
        return true;

    cell unassigned = empty_cells[0];

    // Recursively try every possible number in the first
    // empty cell until the board is full
    for (int i = 1; i <= 9; ++i) {
        brd.put_num(unassigned, i);
        if (brd.is_valid()) {
            if (solve(brd)) {
                return true;
            }
        }

        brd.undo_last_move();
    }

    return false;
}
```

## Build and Run

This program uses the **CMake** build system so it's easy to build and run it. Its only dependency is `SFML 2.5+`. You can follow the instructions on their official [website](https://www.sfml-dev.org/tutorials/2.5/) to install the library.

```sh
git clone https://github.com/RamtinTJB/Sudoku
cd Sudoku
cmake -B build
cd build
make
cd src
./Sudoku
```

It's important to run the program from inside of the `build/src/` directory because the `arial.ttf` font has to be in the current working directory.

If run without any commmand line arguments, it will open a blank Sudoku. You can have it read the Sudoku from a file using `-f`

```sh
> cat puzzle.sdk
0 8 0 5 3 0 2 7 6
0 5 0 6 0 0 0 0 0
6 1 3 0 0 0 0 0 0
0 0 6 0 5 0 0 0 0
0 3 2 0 0 0 7 0 1
7 4 5 0 0 8 6 9 3
0 7 0 9 6 0 5 0 0
4 0 0 1 8 0 0 6 7
5 0 0 0 0 4 8 2 9

> ./Sudoku -f puzzle.sdk
```

## License

<img align="right" src="https://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The project is licensed under the [MIT License](https://opensource.org/licenses/MIT):

Copyright &copy; 2023 Ramtin Tajbakhsh
