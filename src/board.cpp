#include "board.h"

bool board::is_valid() {
	for (int i = 0; i < 9; i++) {
		if (has_duplicate(remove_occurences(get_row(i), 0))) {
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
}

std::vector<int> board::get_all_empty_cells() {
	std::vector<int> res;
	for (int i = 0; i < 81; i++) {
		if (grid_[i] == 0) {
			res.push_back(i);
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

}
