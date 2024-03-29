#include "Giph.h"

Giph::Giph() : board({}), parser(new Parser(&board)), validator(new Validator(&board)) {};
Giph::~Giph() {
	delete parser;
	delete validator;
}

void Giph::Start() {
	while (parser->ParseCommand())
		CommandManager(parser->command);
	CommandManager(parser->command);
}

void Giph::CommandManager(const std::string& command) {
	if (command.compare("LOAD_GAME_BOARD") == 0) {
		parser->ParseGame();
		validator->ValidateBoard();
	}
	else if (command.find("DO_MOVE") != std::string::npos) {
		board.SetMove(command.substr(8, 2), command.substr(11, 2));
		if (command.length() > 13) {
			board.SetPawnCollectInfo(command[14], command.substr(17, 2), command.substr(20, 2));
			validator->ValidateMove(true);
		}
		else validator->ValidateMove();
	}
	else if (command.compare("PRINT_GAME_BOARD") == 0) {
		if (board.isValid) board.PrintGameState();
		else Logger::Log(EMPTY_BOARD);
	}
}



