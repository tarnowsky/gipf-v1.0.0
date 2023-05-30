#pragma once
#include <vector>
#include "Logger.h"

class Board {
public:
	std::vector<std::vector<char>> board;
	bool isValid = false;

	struct BoardInfo {
		int dimension;
		int pawnsToCapture;
		int pawns[2];
		int reserve[2];
		char activePlayer;

	} boardInfo{};

	
	struct BoardExpectedValues {
		std::vector<int> rowWidth;
		int pawnsInTotal[2];
	} boardExpectedValues{};

	struct Position {
		int row, col;
		void Print() const {
			std::cout << row << ", " << col << std::endl;
		}
		bool operator==(const Position& other) const {
			return (row == other.row && col == other.col);
		}
	};
	struct Move {
		std::string from;
		std::string to;
		Position fPosition;
		Position tPosition;
	} move;

	struct Visited {
		static enum Directions {
			LEFT_CORNER,
			UP,
			RIGHT,
			RIGHT_CORNER,
			DOWN,
			LEFT
		} directions;
		bool visitDirection[6] = {};
	};

public:
	void PrintGameState() const;
	void Clear();
	void PrintBoard() const;
	void PrintBoardInfo() const;
	void PrintBoardDev();
	Position FieldDecoder(const std::string& field) const;
	void SetMove(const std::string& from, const std::string& to);
	void MakeMove();
	void MoveRow(int rowOffset, int colOffset, bool isCorner);
};

