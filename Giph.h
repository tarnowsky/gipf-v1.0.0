#pragma once
#include "Parser.h"
#include "Validator.h"

class Giph {
public:
	Board board;
	Parser* parser;
	Validator* validator;
public:
	Giph();
	~Giph();
	void Start();
private:
	void CommandManager(const std::string& command);
};

