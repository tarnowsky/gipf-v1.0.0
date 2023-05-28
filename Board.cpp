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
			if (field && field != '+')
				std::cout << field << ' ';

		std::cout << std::endl;
	}
}

void Board::PrintBoardDev() {
	for (auto& row : board) {
		for (auto& field : row)
		{
			if (field)
				std::cout << field << ' ';
			else std::cout << 0 << ' ';
		}
		std::cout << std::endl;
	}
}

void Board::ValidateBoard() {
	Logger::Log(Validator(this).Validate());
}

Board::Position Board::FieldDecoder(const std::string& field, int dimension) const {
	Board::Position position;
	int rowOffset = 0;
	position.col = field[0] - 'a';
	if (position.col > dimension - 1) {
		rowOffset = position.col - (dimension - 1);
	}
	position.row = (field[1] - '0') - dimension - (field[0] - 'a');
	position.row += rowOffset;
	position.row *= -1;
	return position;
}