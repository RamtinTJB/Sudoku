#ifndef SUDOKU_SOLVER_UTILS_H
#define SUDOKU_SOLVER_UTILS_H

#include <vector>
#include <set>

#include "board.h"

struct cell;

int cell_to_index(const cell& c);
cell index_to_cell(int index);

bool is_index_valid(int index);

template<class T>
bool has_duplicate(const std::vector<T>& vect) {
	std::set<T> s(vect.begin(), vect.end());
	return vect.size() != s.size();
}

template<class T>
std::vector<T> remove_occurences(const std::vector<T>& vect, const T& t) {
	std::vector<T> res;
	for (const auto& item: vect) {
		if (item != t) {
			res.push_back(item);
		}
	}
	return res;
}

#endif
