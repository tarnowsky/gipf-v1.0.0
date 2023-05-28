#include "Parser.h"

Parser::Parser(Board* board) {
	this->board = board;
}

bool Parser::ParseCommand() {
	std::string line;
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\n') break;
		line += (char)c;
	}
	command = line;
	return c != EOF;
}

void Parser::ParseInfo() {
	int c;
	std::string num;
	while (isspace(c = getchar()));
	while (c != ' ') {
		num += c;
		c = getchar();
	}

	board->boardInfo.dimension = std::stoi(num);
	std::cin >> board->boardInfo.pawnsToCapture;
	std::cin >> board->boardInfo.pawns[WHITE];
	std::cin >> board->boardInfo.pawns[BLACK];
	std::cin.get();
	std::cin >> board->boardInfo.reserve[WHITE];
	std::cin >> board->boardInfo.reserve[BLACK];
	std::cin >> board->boardInfo.activePlayer;
	std::cin.get();

	board->boardExpectedValues.pawnsInTotal[WHITE] = board->boardInfo.pawns[WHITE];
	board->boardExpectedValues.pawnsInTotal[BLACK] = board->boardInfo.pawns[BLACK];

	int upDowner = 1;
	for (int i = 0; i != -1; i += upDowner) {
		board->boardExpectedValues.rowWidth.push_back(board->boardInfo.dimension + i);
		if (i == board->boardInfo.dimension - 1) upDowner = -1;
	}
}

bool Parser::ParseBoard() {
	int spacing = board->boardInfo.dimension;
	std::vector<std::vector<char>>& bboard = board->board;

	for (int i = 0; i < 2 * board->boardInfo.dimension + 1; i++) {
		bboard.push_back({});
		std::string line;
		int c;

		if (i == 0 || i == 2 * board->boardInfo.dimension) {
			for (int _ = 0; _ < board->boardInfo.dimension + 1; _++)
				bboard[bboard.size() - 1].push_back('+');
		}
		else {
			while ((c = getchar()) != '\n' && c != EOF)
				line += (char)c;
			if (c == EOF) return false;

			bboard[i].push_back('+');

			for (size_t j = 0; j < line.length(); j++) {
				if (line[j] == ' ') continue;
				bboard[i].push_back(line[j]);
			}

			bboard[i].push_back('+');
		}

		if (spacing > 0)
			for (int _ = 0; _ < spacing; _++)
				bboard[i].push_back(NULL);
		else if (spacing < 0)
			for (int _ = 0; _ > spacing; _--)
				bboard[i].insert(bboard[i].begin(), NULL);

		spacing--;
	}
	return true;
}

void Parser::ParseGame() {
	board->Clear();
	ParseInfo();
	ParseBoard();
}

