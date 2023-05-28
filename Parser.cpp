#include "Parser.h"

Parser::Parser(Board* board) {
	this->board = board;
}

bool Parser::ParseCommand() {
	std::string line;
	while (line.length() == 0) {
		getline(std::cin, line);
		if (std::cin.eof())
			return false;
	}
	command = line;
	return true;
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
	std::cin >> board->boardInfo.startPlayer;
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
	int spacing = board->boardInfo.dimension - 1;
	std::vector<std::vector<char>>& bboard = board->board;

	for (int i = 0; i < 2 * board->boardInfo.dimension - 1; i++) {
		std::string line;
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			line += (char)c;
		if (c == EOF) return false;

		bboard.push_back({});

		for (size_t j = 0; j < line.length(); j++) {
			if (line[j] == ' ') continue;
			bboard[i].push_back(line[j]);
		}

		if (spacing > 0)
			for (int _ = 0; _ < spacing; _++)
				bboard[i].push_back(NULL);
		else
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

