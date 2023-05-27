#pragma once
#include <string>
#include "Board.h"

class Parser {
public:
	std::string command;
public:
	explicit Parser(Board* board);
	bool ParseCommand();
	void ParseGame();
private:
	Board* board;
private:
	void ParseInfo();
	bool ParseBoard();
};