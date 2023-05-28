#include "Validator.h"

Validator::Validator(Board* board) : board(board) {}

void Validator::ValidateBoard() {
	if (CheckBoardRows()) {
		if (CheckPawnsInTotal(WHITE)) {
			if (CheckPawnsInTotal(BLACK)) Logger::Log(BOARD_STATE_OK);
			else Logger::Log(WRONG_BLACK_PAWNS_NUMBER);
		}
		else Logger::Log(WRONG_WHITE_PAWNS_NUMBER);
	}
	else Logger::Log(WRONG_BOARD_ROW_LENGTH);
}

bool Validator::CheckPawnsInTotal(PawnColors pawnColor) const{
	int target = board->boardExpectedValues.pawnsInTotal[pawnColor];
	int counter = board->boardInfo.reserve[pawnColor];
	for (auto& i : board->board) {
		for (auto& j : i) {
			if (pawnColor == WHITE) {
				if (j == 'W')
					counter++;
			}
			else if (j == 'B')
				counter++;

			if (counter > target)
				return false;
		}
	}
	return true;
}

bool Validator::CheckBoardRows() {
	for (size_t row = 0; row < board->board.size(); ++row) {
		if (row == 0 || row == board->board.size() - 1) continue;
		int counter = 0;
		for (auto& field : board->board[row]) {
			if (!field || field == '+') continue;
			counter++;
		}
		if (counter != board->boardExpectedValues.rowWidth[row - 1])
			return false;
	}
	return true;
}
void Validator::ValidateMove(const Board::Move& move) const {
	if (ValidateIndex(move.fPosition, move.from) && ValidateIndex(move.tPosition, move.to))
		if (ValiateStartingField(move.fPosition, move.from) && ValidateDestinationField(move.tPosition, move.to))
			if (ValidateMoveDirection(move.fPosition, move.tPosition))
				if (ValidateFullRow(move.fPosition, move.tPosition))
					board->MakeMove();
}

bool Validator::ValiateStartingField(const Board::Position& position, const std::string& field) const {
	if (board->board[position.row][position.col] != '+') {
		Logger::LogWithField(BAD_MOVE_WRONG_STARTING_FIELD, field);
		return false;
	}
	return true;
}
bool Validator::ValidateIndex(const Board::Position& position, const std::string& field) const {
	int maxVal = board->boardInfo.dimension * 2;
	if (position.row > maxVal || position.col > maxVal ||
		position.row < 0 || position.col < 0 ||
		board->board[position.row][position.col] == NULL) {
		Logger::LogWithField(BAD_MOVE_WRONG_INDEX, field);
		return false;
	}
	return true;
}

bool Validator::ValidateDestinationField(const Board::Position& position, const std::string& field) const {
	if (board->board[position.row][position.col] == '+') {
		Logger::LogWithField(BAD_MOVE_WRONG_DESTINATION_FIELD, field);
		return false;
	}
	return true;
}

bool Validator::ValidateMoveDirection(const Board::Position& from, const Board::Position& to) const {
	for (auto& possiblePosition : GetPossibleMoves(from))
		if (possiblePosition == to)
			return true;
	Logger::Log(UNKNOWN_MOVE_DIRECTION);
	return false;
}

std::vector<Board::Position> Validator::GetPossibleMoves(const Board::Position& position) const {
	std::vector<Board::Position> possibleMoves;
	if (position.row == 0) {
		if (position.col == 0) {
			possibleMoves.push_back({ position.row + 1, position.col + 1 });
		}
		else if (position.col == board->boardInfo.dimension) {
			possibleMoves.push_back({ position.row + 1, position.col });
		}
		else {
			possibleMoves.push_back({ position.row + 1, position.col });
			possibleMoves.push_back({ position.row + 1, position.col + 1 });
		}
	}
	else if (position.row == board->boardInfo.dimension) {
		if (position.col == 0) {
			possibleMoves.push_back({ position.row, position.col + 1 });
		}
		else if (position.col == board->boardInfo.dimension * 2) {
			possibleMoves.push_back({ position.row, position.col - 1 });
		}
	}

	else if (position.row == board->boardInfo.dimension * 2) {
		if (position.col == board->boardInfo.dimension) {
			possibleMoves.push_back({ position.row - 1, position.col });
		}
		else if (position.col == board->boardInfo.dimension * 2) {
			possibleMoves.push_back({ position.row - 1, position.col - 1 });
		}
		else {
			possibleMoves.push_back({ position.row - 1, position.col });
			possibleMoves.push_back({ position.row - 1, position.col - 1 });
		}
	}
	else {
		if (position.col < board->boardInfo.dimension) {
			possibleMoves.push_back({ position.row - 1, position.col });
			possibleMoves.push_back({ position.row, position.col + 1 });
		}
		else {
			possibleMoves.push_back({ position.row + 1, position.col });
			possibleMoves.push_back({ position.row, position.col - 1 });
		}
	}

	return possibleMoves;
}



bool Validator::ValidateFullRow(const Board::Position& from, const Board::Position& to) const {
	int counter = 0;
	if (from.row == 0) {
		if (from.col == 0)
			CheckRow(from, counter, 1, 1);
		else if (from.col == board->boardInfo.dimension)
			CheckRow(from, counter, 1, 0);
		else {
			if (to.col == from.col) CheckRow(from, counter, 1, 0);
			else CheckRow(from, counter, 1, 1);
		}
	}
	else if (from.row == board->boardInfo.dimension) {
		if (from.col == 0)
			CheckRow(from, counter, 0, 1);
		else if (from.col == board->boardInfo.dimension * 2)
			CheckRow(from, counter, 0, -1);
	}
	else if (from.row == board->boardInfo.dimension * 2) {
		if (from.col == board->boardInfo.dimension)
			CheckRow(from, counter, -1, 0);
		else if (from.col == board->boardInfo.dimension * 2) 
			CheckRow(from, counter, -1, -1);
		else {
			if (to.col == from.col) CheckRow(from, counter, -1, 0);
			else CheckRow(from, counter, -1, -1);
		}
	}
	else {
		if (from.col < board->boardInfo.dimension) {
			if (from.row == to.row) CheckRow(from, counter, 0, 1);
			else CheckRow(from, counter, -1, 0);
		}
		else {
			if (from.row == to.row) CheckRow(from, counter, 0, -1);
			else CheckRow(from, counter, 1, 0);
		}
	}
	if (!counter) {
		Logger::Log(BAD_MOVE_ROW_IS_FULL);
		return false;
	}
	return true;
}

void Validator::CheckRow(const Board::Position from, int& counter, int rowOffset, int colOffset) const {
	for (int i = 0; i < board->boardInfo.dimension * 2 - 1; i++) {
		if (board->board[from.row + rowOffset + i * rowOffset][from.col + colOffset + i * colOffset] == '_') {
			counter++;
			break;
		}
	}
}