#ifndef SUDOKU_SOLVER_BOARD_H
#define SUDOKU_SOLVER_BOARD_H

#include <iostream>
#include <vector>
#include <stack>

#include "utils.h"

enum class CellStyle {
	REGULAR,
	GREEN,
	RED
};

struct cell {
	int row;
	int col;
};

class board {
	private:
		int* grid_ = nullptr;
		CellStyle* styles_ = nullptr;
		std::stack<int> move_index_history_;

		std::vector<int> get_row(int row_num) const;
		std::vector<int> get_col(int col_num) const;
		std::vector<int> get_box(int box_num) const;
	public:
		board();

		bool is_valid();
		void put_num(const cell& c, int num);
        void clear_cell(const cell&);
		void undo_last_move();
		std::vector<cell> get_all_empty_cells();
		bool is_board_full();
		int get_num(const cell&) const;

		CellStyle get_style(const cell& c) const;
		void set_style(const cell&, const CellStyle&);

		void print_board();
};


#endif
