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
		int dimension;
		int pawnsToCapture;
		int pawns[2];
		int reserve[2];
		char startPlayer;

	} boardInfo{};

	std::vector<std::vector<char>> board;
	
	struct BoardExpectedValues {
		std::vector<int> rowWidth;
		int pawnsInTotal[2];
	} boardExpectedValues{};

	struct Position {
		int row, col;
		void Print() const {
			std::cout << row << ", " << col << std::endl;
		}
	};


public:
	void Clear();
	void PrintBoard();
	void PrintBoardDev();
	void ValidateBoard();
	Position FieldDecoder(const std::string& field, int dimension) const;
	void ValidateMove(const std::string& from, const std::string to) {
		Position fPosition = FieldDecoder(from, boardInfo.dimension);
		Position tPosition = FieldDecoder(to, boardInfo.dimension);
		if (ValidatePosition(fPosition, from) && ValidatePosition(tPosition, to)) {
			Logger::Log(MOVE_COMMITTED);
		}
	}
	bool ValidatePosition(const Position& position, const std::string &field ) {
		int maxVal = boardInfo.dimension*2-2;
		if (position.row > maxVal || position.col > maxVal ||
			position.row < 0 || position.col < 0 ||
			board[position.row][position.col] == NULL) {
			Logger::LogWithPosition(BAD_MOVE_WRONG_INDEX, field);
			return false;
		}
		return true;
	}

};

