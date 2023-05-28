#include "Board.h"

Validator::Validator(Board* board) : board(board) {}

ReturnLogs Validator::Validate() {
	if (CheckBoardRows()) {
		if (CheckPawnsInTotal(WHITE)) {
			if (CheckPawnsInTotal(BLACK)) return BOARD_STATE_OK;
			else return WRONG_BLACK_PAWNS_NUMBER;
		}
		else return WRONG_WHITE_PAWNS_NUMBER;
	}
	else return WRONG_BOARD_ROW_LENGTH;
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