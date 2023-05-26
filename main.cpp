#include <iostream>
#include <string>
#include <vector>

constexpr short START_PAWNS = 3;

class Parser {
private:
	struct BoardInfo {
		int x, y;
		int wPawns, bPawns;
		int wReserve, bReserve;
		char startPlayer;

		void Print() {
			std::cout << "x -> " << x << std::endl;
			std::cout << "y -> " << y << std::endl;
			std::cout << "wPawns -> " << wPawns << std::endl;
			std::cout << "bPawns -> " << bPawns << std::endl;
			std::cout << "wReserve -> " << wReserve << std::endl;
			std::cout << "bReserve -> " << bReserve << std::endl;
			std::cout << "startPlayer -> " << startPlayer << std::endl;
		}

	} boardInfo{};

	struct BoardExpectedValues {
		std::vector<int> rowWidth;
		int pawnsOnBoard[2];
	} boardExpectedValues{};

	enum Commands {
		LOAD_GAME_BOARD,
		PRINT_GAME_BOARD,
		DO_MOVE,
	};

	enum PawnColors {
		WHITE,
		BLACK,
	};

	std::vector<std::vector<char>> board;
public:

	enum ReturnLogs {
		END_OF_FILE,
		BOARD_STATE_OK,
		WRONG_WHITE_PAWNS_NUMBER,
		WRONG_BLACK_PAWNS_NUMBER,
		WRONG_BOARD_ROW_LENGTH,
	};

	ReturnLogs Parse() {
		ParseInfo();
		ParseBoard();
		return {};
	}

	void Log(ReturnLogs returnLog) {
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

	void PrintBoard() {
		for (auto& i : board) {
			for (auto& j : i)
				std::cout << j << ' ';
			std::cout << std::endl;
		}
	}

	void LogPawnsState() {
		std::cout << "white -> ";
		Log(CheckPawnsOnBoard(WHITE) ? BOARD_STATE_OK : WRONG_WHITE_PAWNS_NUMBER);
		std::cout << "black -> ";
		Log(CheckPawnsOnBoard(BLACK) ? BOARD_STATE_OK : WRONG_BLACK_PAWNS_NUMBER);
	}

	bool ParseCommand() {
		std::string line;
		while(line.length() == 0) {
			getline(std::cin, line);
			if (std::cin.eof())
				return false;
		}
		if (line.compare("LOAD_GAME_BOARD") == 0) {
			Parse();
		}
		return true;
	}

	void Clear() {
		for (auto& i : board)
			i.clear();
		board.clear();
		boardExpectedValues.rowWidth.clear();
	}

	void LogBoardStateInfo() {
		if (CheckBoardRows() == BOARD_STATE_OK) {
			if (CheckPawnsOnBoard(WHITE) == BOARD_STATE_OK) {
				if (CheckPawnsOnBoard(BLACK) == BOARD_STATE_OK) Log(BOARD_STATE_OK);
				else Log(WRONG_BLACK_PAWNS_NUMBER);
			} else Log(WRONG_WHITE_PAWNS_NUMBER);
		} else Log(WRONG_BOARD_ROW_LENGTH);
		Clear();
	}
private:
	void ParseInfo() {
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

	bool ParseBoard() {
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

	bool CheckPawnsOnBoard(PawnColors pawnColor) {
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

	bool CheckBoardRows() {
		for (int row = 0; row < board.size(); ++row)
			if (board[row].size() != boardExpectedValues.rowWidth[row])
				return false;
		return true;
	}
	
};

int main() {
	Parser p;
	while (p.ParseCommand()) {
		p.LogBoardStateInfo();
	}
}

//std::cout << "bool ->\t\t" << sizeof(bool) << " bytes" << std::endl;
//std::cout << "char ->\t\t" << sizeof(char) << " bytes" << std::endl;
//std::cout << "short ->\t" << sizeof(short) << " bytes" << std::endl;
//std::cout << "int ->\t\t" << sizeof(int) << " bytes" << std::endl;
//std::cout << "long ->\t\t" << sizeof(long) << " bytes" << std::endl;
//std::cout << "float ->\t" << sizeof(float) << " bytes" << std::endl;
//std::cout << "double ->\t" << sizeof(double) << " bytes" << std::endl;
//std::cout << "long long ->\t" << sizeof(long long) << " bytes" << std::endl;