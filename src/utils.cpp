#include "utils.h"

int cell_to_index(const cell& c) {
	return c.row*9 + c.col;
}

cell index_to_cell(int index) {
	cell c;
	c.row = index / 9;
	c.col = index % 9;
	return c;
}

bool is_index_valid(int index) {
	return index >= 0 && index <= 80;
}
