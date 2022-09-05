#ifndef SUDOKU_SOLVER_BOARD_H
#define SUDOKU_SOLVER_BOARD_H

#include <iostream>
#include <vector>

#include "utils.h"

struct cell {
	int row;
	int col;
};

class board {
	private:
		int* grid_ = new int[81];
		std::vector<int> get_row(int row_num) const;
		std::vector<int> get_col(int col_num) const;
		std::vector<int> get_box(int box_num) const;
	public:
		bool is_valid();
		void put_num(const cell& c, int num);
		std::vector<int> get_all_empty_cells();
		bool is_board_full();
};


#endif
