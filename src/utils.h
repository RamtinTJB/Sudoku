#ifndef SUDOKU_SOLVER_UTILS_H
#define SUDOKU_SOLVER_UTILS_H

#include "board.h"

struct cell;

int cell_to_index(const cell& c);

cell index_to_cell(int index);

#endif
