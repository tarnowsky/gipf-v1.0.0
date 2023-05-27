#include "Giph.h"

Giph::Giph() : board({}), parser(new Parser(&board)) {};
Giph::~Giph() {
	delete parser;
}

void Giph::Start() {
	while (parser->ParseCommand()) {
		CommandManager(parser->command);
	}
}

void Giph::CommandManager(std::string command) {
	if (command.compare("LOAD_GAME_BOARD") == 0) {
		parser->ParseGame();
		board.ValidateBoard();
	}
}