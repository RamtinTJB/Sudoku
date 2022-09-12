#include <iostream>

#include "solver.h"

int main(int argc, const char** argv) {
	board brd;
	solve(brd);

	brd.print_board();

	return 0;
}
