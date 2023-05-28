#include "Board.h"

void Board::Clear() {
	for (auto& i : board)
		i.clear();
	board.clear();
	boardExpectedValues.rowWidth.clear();
}

void Board::PrintBoard() {
	int toggle = 1;
	int numOfSpace = boardInfo.dimension;

	for (auto& row : board) {
		numOfSpace -= 1 * toggle;
		for (int i = 0; i < numOfSpace; i++)
			std::cout << ' ';

		if (!numOfSpace)
			toggle *= -1;

		for (auto& field : row)
			if (field)
				std::cout << field << ' ';

		std::cout << std::endl;
	}
}

void Board::ValidateBoard() {
	Logger::Log(Validator(this).Validate());
}