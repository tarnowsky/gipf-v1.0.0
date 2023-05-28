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

Board::Position Giph::FieldDecoder(std::string field, int dimension) const {
	Board::Position position;
	int rowOffset = 0;
	position.col = field[0] - 'a';
	if (position.col > dimension - 1) {
		rowOffset = position.col - (dimension - 1);
	}
	position.row = (field[1] - '0') - dimension - (field[0] - 'a');
	position.row += rowOffset;
	position.row *= -1;
	return position;
}