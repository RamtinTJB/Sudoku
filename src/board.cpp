#include "board.h"

#include <algorithm>

void board::init_cell_styles() {
    styles_ = new CellStyle[81];
    for (int i = 0; i < 81; ++i) {
        styles_[i] = CellStyle::REGULAR;
    }
}

board::board() {
    init_cell_styles();
}

void board::fill(const std::vector<int>& number) {
    std::copy(number.begin(), number.end(), grid_);
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

void board::clear_cell(const cell& c) {
    int index = cell_to_index(c);
    if (is_index_valid(index)) {
        grid_[index] = 0;
    }
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

board::~board() {
    delete[] grid_;
    delete[] styles_;
}
