#pragma once
#include <string>
#include <vector>
#include <iostream>

class Parser {
	enum ReturnLogs;
public:
	bool ParseCommand();
	void LogBoardStateInfo();

public:
	void Parse();
	void Log(ReturnLogs returnLog);
	void PrintBoard();
	void LogPawnsState();
	void Clear();

private:
	struct BoardInfo {
		int x, y;
		int wPawns, bPawns;
		int wReserve, bReserve;
		char startPlayer;

		void Print() {
			std::cout << "x -> " << x << std::endl;
			std::cout << "y -> " << y << std::endl;
			std::cout << "wPawns -> " << wPawns << std::endl;
			std::cout << "bPawns -> " << bPawns << std::endl;
			std::cout << "wReserve -> " << wReserve << std::endl;
			std::cout << "bReserve -> " << bReserve << std::endl;
			std::cout << "startPlayer -> " << startPlayer << std::endl;
		}

	} boardInfo;

	struct BoardExpectedValues {
		std::vector<int> rowWidth;
		int pawnsOnBoard[2];
	} boardExpectedValues;

	enum Commands {
		LOAD_GAME_BOARD,
		PRINT_GAME_BOARD,
		DO_MOVE,
	};

	enum PawnColors {
		WHITE,
		BLACK,
	};

	enum ReturnLogs {
		BOARD_STATE_OK,
		WRONG_WHITE_PAWNS_NUMBER,
		WRONG_BLACK_PAWNS_NUMBER,
		WRONG_BOARD_ROW_LENGTH,
	};
public:
	std::vector<std::vector<char>> board;

private:
	void ParseInfo();
	bool ParseBoard();
	bool CheckPawnsOnBoard(PawnColors pawnColor);
	bool CheckBoardRows();
};