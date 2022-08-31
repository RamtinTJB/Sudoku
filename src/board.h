#ifndef SUDOKU_SOLVER_BOARD_H
#define SUDOKU_SOLVER_BOARD_H

#include <iostream>
#include <vector>

struct cell {
	int row;
	int col;
};

class board {
	private:
		int* grid_ = new int[81];
	public:
};


#endif
