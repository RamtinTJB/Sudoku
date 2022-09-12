#ifndef SUDOKU_SOLVER_BOARD_H
#define SUDOKU_SOLVER_BOARD_H

#include <iostream>
#include <vector>
#include <stack>

#include "utils.h"

struct cell {
	int row;
	int col;
};

class board {
	private:
		int* grid_;
		std::stack<int> move_index_history_;

		std::vector<int> get_row(int row_num) const;
		std::vector<int> get_col(int col_num) const;
		std::vector<int> get_box(int box_num) const;
	public:
		board();

		bool is_valid();
		void put_num(const cell& c, int num);
		void undo_last_move();
		std::vector<cell> get_all_empty_cells();
		bool is_board_full();

		void print_board();
};


#endif
