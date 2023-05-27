#include "Board.h"

void Board::Clear() {
	for (auto& i : board)
		i.clear();
	board.clear();
	boardExpectedValues.rowWidth.clear();
}

void Board::PrintBoard() {
	for (auto& i : board) {
		for (auto& j : i)
			std::cout << j << ' ';
		std::cout << std::endl;
	}
}