#include "solver.h"

bool solve(board& brd, std::function<void(void)> gui_callback) {
	std::vector<cell> empty_cells = brd.get_all_empty_cells();

	if (empty_cells.empty())
		return true;

	cell unassigned = empty_cells[0];

	for (int i = 1; i <= 9; i++) {
		brd.put_num(unassigned, i);
		if (brd.is_valid()) {
			brd.set_style(unassigned, CellStyle::GREEN);
			gui_callback();

			if (solve(brd, gui_callback)) {
				return true;
			}
		} else {
			brd.set_style(unassigned, CellStyle::RED);
			gui_callback();
		}
		brd.undo_last_move();
	}

	return false;
}
