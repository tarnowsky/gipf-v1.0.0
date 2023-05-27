#pragma once
#include <vector>
#include "Logger.h"

class Board;

class Validator {
public:
	explicit Validator(Board* board);
	ReturnLogs Validate();
private:
	Board* board;
	bool CheckPawnsInTotal(PawnColors pawnColor) const;
	bool CheckBoardRows();
};


class Board {
public:
	struct BoardInfo {
		int x, y;
		int pawns[2];
		int reserve[2];
		char startPlayer;

	} boardInfo{};

	std::vector<std::vector<char>> board;

	struct BoardExpectedValues {
		std::vector<int> rowWidth;
		int pawnsInTotal[2];
	} boardExpectedValues{};
public:
	void Clear();
	void PrintBoard();
	void ValidateBoard() {
		Logger::Log(Validator(this).Validate());
	}
};

