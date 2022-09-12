#include "solver.h"

bool solve(board& brd) {
	std::vector<cell> empty_cells = brd.get_all_empty_cells();

	if (empty_cells.empty())
		return true;

	cell unassigned = empty_cells[0];

	for (int i = 1; i <= 9; i++) {
		brd.put_num(unassigned, i);
		if (brd.is_valid()) {
			if (solve(brd)) {
				return true;
			}
		}
		brd.undo_last_move();
	}

	return false;
}
