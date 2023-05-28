#include "Board.h"

void Board::PrintGameState() const {
	PrintBoardInfo();
	PrintBoard();
}

void Board::Clear() {
	for (auto& i : board)
		i.clear();
	board.clear();
	boardExpectedValues.rowWidth.clear();
}

void Board::PrintBoard() const {
	int toggle = 1;
	int numOfSpace = boardInfo.dimension;

	for (int row = 1; row < board.size() - 1; row++) {

		numOfSpace -= 1 * toggle;
		for (int i = 0; i < numOfSpace; i++)
			std::cout << ' ';

		if (!numOfSpace)
			toggle *= -1;

		for (auto& field : board[row])
			if (field && field != '+')
				std::cout << field << ' ';

		std::cout << std::endl;
	}
}

void Board::PrintBoardInfo() const {
	std::cout << boardInfo.dimension << " ";
	std::cout << boardInfo.pawnsToCapture << " ";
	std::cout << boardInfo.pawns[WHITE] << " ";
	std::cout << boardInfo.pawns[BLACK] << std::endl;

	std::cout << boardInfo.reserve[WHITE] << " ";
	std::cout << boardInfo.reserve[BLACK] << " ";
	std::cout << boardInfo.activePlayer << std::endl;
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

Board::Position Board::FieldDecoder(const std::string& field) const{
	Board::Position position;
	int rowOffset = 0;
	position.col = field[0] - 'a';
	if (position.col > boardInfo.dimension) {
		rowOffset = position.col - (boardInfo.dimension);
	}
	position.row = (field[1] - '0') - boardInfo.dimension - 1 - (field[0] - 'a');
	position.row += rowOffset;
	position.row *= -1;
	return position;
}

void Board::MoveRow(int rowOffset, int colOffset, bool isCorner) {
	char pawnToPlace = boardInfo.activePlayer;
	for (int i = 0; i < boardInfo.dimension * 2 - (isCorner ? 1 : 2); i++) {
		int row = move.tPosition.row + i * rowOffset;
		int col = move.tPosition.col + i * colOffset;
		char nextPawn = board[row][col];
		board[row][col] = pawnToPlace;
		if (nextPawn == '_') break;
		pawnToPlace = nextPawn;
	}
	Logger::Log(MOVE_COMMITTED);
}

void Board::MakeMove() {
	--boardInfo.reserve[boardInfo.activePlayer == 'W' ? WHITE : BLACK];

	if (move.fPosition.row == 0) {
		if (move.fPosition.col == 0)
			MoveRow(1, 1, true);
		else if (move.fPosition.col == boardInfo.dimension)
			MoveRow(1, 0, true);
		else {
			if (move.tPosition.col == move.fPosition.col)
				MoveRow(1, 0, false);
			else
				MoveRow(1, 1, false);
		}
	}
	else if (move.fPosition.row == boardInfo.dimension) {
		if (move.fPosition.col == 0)
			MoveRow(0, 1, true);
		else if (move.fPosition.col == boardInfo.dimension * 2)
			MoveRow(0, -1, true);
	}
	else if (move.fPosition.row == boardInfo.dimension * 2) {
		if (move.fPosition.col == boardInfo.dimension)
			MoveRow(-1, 0, true);
		else if (move.fPosition.col == boardInfo.dimension * 2)
			MoveRow(-1, -1, true);
		else {
			if (move.tPosition.col == move.fPosition.col)
				MoveRow(-1, 0, false);
			else
				MoveRow(-1, -1, false);
		}
	}
	else {
		if (move.fPosition.col < boardInfo.dimension) {
			if (move.fPosition.row == move.tPosition.row)
				MoveRow(0, 1, false);
			else
				MoveRow(-1, 0, false);
		}
		else {
			if (move.fPosition.row == move.tPosition.row)
				MoveRow(0, -1, false);
			else
				MoveRow(1, 0, false);
		}
	}
	boardInfo.activePlayer = boardInfo.activePlayer == 'W' ? 'B' : 'W';
}

void Board::SetMove(const std::string& from, const std::string& to) {
	move.from = from;
	move.to = to;
	move.fPosition = FieldDecoder(from);
	move.tPosition = FieldDecoder(to);
}