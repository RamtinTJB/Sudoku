#include "board.h"

board::board() {
	grid_ = new int[81] {0, 8, 0, 5, 3, 0, 2, 7, 6,
						 0, 5, 0, 6, 0, 0, 0, 0, 0,
						 6, 1, 3, 0, 0, 0, 0, 0, 0,
						 0, 0, 6, 0, 5, 0, 0, 0, 0,
						 0, 3, 2, 0, 0, 0, 7, 0, 1,
						 7, 4, 5, 0, 0, 8, 6, 9, 3,
						 0, 7, 0, 9, 6, 0, 5, 0, 0, 4, 0, 0, 1, 8, 0, 0, 6, 7,
						 5, 0, 0, 0, 0, 4, 8, 2, 9};	
	styles_ = new CellStyle[81];	
	for (int i = 0; i < 81; ++i) {
		styles_[i] = CellStyle::REGULAR;
	}
}

bool board::is_valid() {
	for (int i = 0; i < 9; i++) {
		if (has_duplicate(remove_occurences(get_row(i), 0)) ||
				has_duplicate(remove_occurences(get_col(i), 0)) ||
				has_duplicate(remove_occurences(get_box(i), 0))) {
			return false;
		}
	}

	return true;
}

void board::put_num(const cell& c, int num) {
	int index = cell_to_index(c);
	if (is_index_valid(index)) {
		grid_[index] = num;
	}
	move_index_history_.push(index);
}

int board::get_num(const cell& c) const {
	int index = cell_to_index(c);
	if (is_index_valid(index)) {
		return grid_[index];
	}
	return -1;
}

CellStyle board::get_style(const cell& c) const {
	int index = cell_to_index(c);
	if (is_index_valid(index)) {
		return styles_[index];
	}
	return CellStyle::REGULAR;
}

void board::set_style(const cell& c, const CellStyle& style) {
	int index = cell_to_index(c);
	if (is_index_valid(index)) {
		styles_[index] = style;
	}
}

void board::undo_last_move() {
	int index = move_index_history_.top();
	grid_[index] = 0;
	move_index_history_.pop();
}

std::vector<cell> board::get_all_empty_cells() {
	std::vector<cell> res;
	for (int i = 0; i < 81; i++) {
		if (grid_[i] == 0) {
			res.push_back(index_to_cell(i));
		}
	}
	return res;
}

bool board::is_board_full() {
	return get_all_empty_cells().empty();
}

std::vector<int> board::get_row(int row_num) const {
	std::vector<int> res;
	for (int i = 0; i < 9; i++) {
		res.push_back(grid_[row_num*9+i]);
	}
	return res;
}

std::vector<int> board::get_col(int col_num) const {
	std::vector<int> res;
	for (int i = 0; i < 9; i++) {
		res.push_back(grid_[i*9 + col_num]);
	}
	return res;
}

std::vector<int> board::get_box(int box_num) const {
	std::vector<int> res;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cell c;
			c.row = (box_num/3)*3 + i;
			c.col = (box_num%3)*3 + j;
			res.push_back(grid_[cell_to_index(c)]);
		}
	}
	return res;
}

void board::print_board() {
	for (int i = 0; i < 81; i++) {
		if (i % 9 ==0) std::cout << std::endl;
		std::cout << grid_[i] << " ";
	}
}
