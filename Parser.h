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
	void ParseInfo();
	bool ParseBoard();
private:
	Board* board;
};