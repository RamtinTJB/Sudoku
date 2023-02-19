#ifndef SUDOKU_SOLVER_SOLVER_H
#define SUDOKU_SOLVER_SOLVER_H

#include <iostream>
#include <functional>

#include "board.h"

bool solve(board& brd, std::function<void(void)> gui_callback);

#endif
