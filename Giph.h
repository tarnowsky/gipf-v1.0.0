#pragma once
#include "Parser.h"

class Giph {
public:
	Board board;
	Parser* parser;
	Giph();
	~Giph();
	void Start();
private:
	void CommandManager(const std::string& command);
public:
	

};

