#include "Parser.h"

void Parser::Log(ReturnLogs returnLog) {
	switch (returnLog) {
	case Parser::BOARD_STATE_OK:
		std::cout << "BOARD_STATE_OK";
		break;
	case Parser::WRONG_WHITE_PAWNS_NUMBER:
		std::cout << "WRONG_WHITE_PAWNS_NUMBER";
		break;
	case Parser::WRONG_BLACK_PAWNS_NUMBER:
		std::cout << "WRONG_BLACK_PAWNS_NUMBER";
		break;
	case Parser::WRONG_BOARD_ROW_LENGTH:
		std::cout << "WRONG_BOARD_ROW_LENGTH";
		break;
	}
	std::cout << std::endl;
}

void Parser::PrintBoard() {
	for (auto& i : board) {
		for (auto& j : i)
			std::cout << j << ' ';
		std::cout << std::endl;
	}
}

void Parser::LogPawnsState() {
	std::cout << "white -> ";
	Log(CheckPawnsOnBoard(WHITE) ? BOARD_STATE_OK : WRONG_WHITE_PAWNS_NUMBER);
	std::cout << "black -> ";
	Log(CheckPawnsOnBoard(BLACK) ? BOARD_STATE_OK : WRONG_BLACK_PAWNS_NUMBER);
}

bool Parser::ParseCommand() {
	std::string line;
	while (line.length() == 0) {
		getline(std::cin, line);
		if (std::cin.eof())
			return false;
	}
	if (line.compare("LOAD_GAME_BOARD") == 0) {
		Parse();
	}
	return true;
}

void Parser::Clear() {
	for (auto& i : board)
		i.clear();
	board.clear();
	boardExpectedValues.rowWidth.clear();
}

 void Parser::LogBoardStateInfo() {
	if (CheckBoardRows()) {
		if (CheckPawnsOnBoard(WHITE)) {
			if (CheckPawnsOnBoard(BLACK)) Log(BOARD_STATE_OK);
			else Log(WRONG_BLACK_PAWNS_NUMBER);
		}
		else Log(WRONG_WHITE_PAWNS_NUMBER);
	}
	else Log(WRONG_BOARD_ROW_LENGTH);
	Clear();
}

void Parser::ParseInfo() {
	int c;
	std::string num;
	while (isspace(c = getchar()));
	while (c != ' ') {
		num += c;
		c = getchar();
	}

	boardInfo.x = std::stoi(num);
	std::cin >> boardInfo.y;
	std::cin >> boardInfo.wPawns;
	std::cin >> boardInfo.bPawns;
	std::cin.get();
	std::cin >> boardInfo.wReserve;
	std::cin >> boardInfo.bReserve;
	std::cin >> boardInfo.startPlayer;
	std::cin.get();

	boardExpectedValues.pawnsOnBoard[WHITE] = boardInfo.wPawns - boardInfo.wReserve;
	boardExpectedValues.pawnsOnBoard[BLACK] = boardInfo.bPawns - boardInfo.bReserve;

	int upDowner = 1;
	for (int i = 0; i != -1; i += upDowner) {
		boardExpectedValues.rowWidth.push_back(boardInfo.x + i);
		if (i == boardInfo.x - 1) upDowner = -1;
	}
}

bool Parser::ParseBoard() {
	for (int i = 0; i < 2 * boardInfo.x - 1; i++) {
		std::string line;
		char c;
		while ((c = getchar()) != '\n' && c != EOF)
			line += c;
		if (c == EOF) return false;

		board.push_back({});

		for (int j = 0; j < line.length(); j++) {
			if (line[j] == ' ') continue;
			board[i].push_back(line[j]);
		}
	}
	return true;
}

void Parser::Parse() {
	ParseInfo();
	ParseBoard();
}

bool Parser::CheckPawnsOnBoard(PawnColors pawnColor) {
	int target = boardExpectedValues.pawnsOnBoard[pawnColor];
	int counter = 0;
	for (auto& i : board) {
		for (auto& j : i) {
			if (pawnColor == WHITE) {
				if (j == 'W')
					counter++;
			}
			else if (j == 'B')
				counter++;

			if (counter > target)
				return false;
		}
	}
	if (counter != target)
		return false;
	return true;
}

bool Parser::CheckBoardRows() {
	for (int row = 0; row < board.size(); ++row)
		if (board[row].size() != boardExpectedValues.rowWidth[row])
			return false;
	return true;
}