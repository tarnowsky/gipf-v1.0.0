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
	for (size_t row = 0; row < board->board.size(); ++row)
		if (board->board[row].size() != (size_t)board->boardExpectedValues.rowWidth[row])
			return false;
	return true;
}