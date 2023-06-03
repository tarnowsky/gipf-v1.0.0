#include "Validator.h"

Validator::Validator(Board* board) : board(board) {}

void Validator::ValidateBoard() {
	if (CheckBoardRows()) {
		if (CheckPawnsInTotal(WHITE)) {
			if (CheckPawnsInTotal(BLACK)) {
				int chains = FindChains();
				if (!chains) {
					board->isValid = true;
					Logger::Log(BOARD_STATE_OK);
				}
				else Logger::LogWithNum(ERROR_FOUND_ROW_OF_LENGTH_K, chains);
			}
			else Logger::Log(WRONG_BLACK_PAWNS_NUMBER);
		}
		else Logger::Log(WRONG_WHITE_PAWNS_NUMBER);
	}
	else Logger::Log(WRONG_BOARD_ROW_LENGTH);
}

bool Validator::CheckPawnsInTotal(PawnColors pawnColor) const{
	int target = board->boardExpectedValues.pawnsInTotal[pawnColor];
	int counter = board->boardInfo.reserve[pawnColor];
	for (auto& i : board->board) {
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
	return true;
}

bool Validator::CheckBoardRows() {
	for (size_t row = 0; row < board->board.size(); ++row) {
		if (row == 0 || row == board->board.size() - 1) continue;
		int counter = 0;
		for (auto& field : board->board[row]) {
			if (!field || field == '+') continue;
			counter++;
		}
		if (counter != board->boardExpectedValues.rowWidth[row - 1])
			return false;
	}
	return true;
}
void Validator::ValidateMove(bool extend) const {
	if (ValidateIndex(board->move.fPosition, board->move.from) && ValidateIndex(board->move.tPosition, board->move.to))
		if (ValiateStartingField(board->move.fPosition, board->move.from) && ValidateDestinationField(board->move.tPosition, board->move.to))
			if (ValidateMoveDirection(board->move.fPosition, board->move.tPosition))
				if (ValidateFullRow(board->move.fPosition, board->move.tPosition)) {
					if (extend) {
						board->MakeMove();
						if (ValidateMoveExtend()) {
							FindChains(COLLECT_PAWNS);
							board->NextPlayer();
							Logger::Log(MOVE_COMMITTED);
						}
					}
					else {
						board->MakeMove();
						FindChains(COLLECT_PAWNS);
						board->NextPlayer();
						Logger::Log(MOVE_COMMITTED);
					}
				}
}

bool Validator::ValiateStartingField(const Board::Position& position, const std::string& field) const {
	if (board->board[position.row][position.col] != '+') {
		Logger::LogWithField(BAD_MOVE_WRONG_STARTING_FIELD, field);
		return false;
	}
	return true;
}
bool Validator::ValidateIndex(const Board::Position& position, const std::string& field) const {
	int maxVal = board->boardInfo.dimension * 2;
	if (position.row > maxVal || position.col > maxVal ||
		position.row < 0 || position.col < 0 ||
		board->board[position.row][position.col] == NULL) {
		Logger::LogWithField(BAD_MOVE_WRONG_INDEX, field);
		return false;
	}
	return true;
}

bool Validator::ValidateDestinationField(const Board::Position& position, const std::string& field) const {
	if (board->board[position.row][position.col] == '+') {
		Logger::LogWithField(BAD_MOVE_WRONG_DESTINATION_FIELD, field);
		return false;
	}
	return true;
}

bool Validator::ValidateMoveDirection(const Board::Position& from, const Board::Position& to) const {
	for (auto& possiblePosition : GetPossibleMoves(from))
		if (possiblePosition == to)
			return true;
	Logger::Log(UNKNOWN_MOVE_DIRECTION);
	return false;
}

std::vector<Board::Position> Validator::GetPossibleMoves(const Board::Position& position) const {
	std::vector<Board::Position> possibleMoves;
	if (position.row == 0) {
		if (position.col == 0) {
			possibleMoves.push_back({ position.row + 1, position.col + 1 });
		}
		else if (position.col == board->boardInfo.dimension) {
			possibleMoves.push_back({ position.row + 1, position.col });
		}
		else {
			possibleMoves.push_back({ position.row + 1, position.col });
			possibleMoves.push_back({ position.row + 1, position.col + 1 });
		}
	}
	else if (position.row == board->boardInfo.dimension) {
		if (position.col == 0) {
			possibleMoves.push_back({ position.row, position.col + 1 });
		}
		else if (position.col == board->boardInfo.dimension * 2) {
			possibleMoves.push_back({ position.row, position.col - 1 });
		}
	}

	else if (position.row == board->boardInfo.dimension * 2) {
		if (position.col == board->boardInfo.dimension) {
			possibleMoves.push_back({ position.row - 1, position.col });
		}
		else if (position.col == board->boardInfo.dimension * 2) {
			possibleMoves.push_back({ position.row - 1, position.col - 1 });
		}
		else {
			possibleMoves.push_back({ position.row - 1, position.col });
			possibleMoves.push_back({ position.row - 1, position.col - 1 });
		}
	}
	else {
		if (position.col < board->boardInfo.dimension) {
			possibleMoves.push_back({ position.row - 1, position.col });
			possibleMoves.push_back({ position.row, position.col + 1 });
		}
		else {
			possibleMoves.push_back({ position.row + 1, position.col });
			possibleMoves.push_back({ position.row, position.col - 1 });
		}
	}

	return possibleMoves;
}



bool Validator::ValidateFullRow(const Board::Position& from, const Board::Position& to) const {
	int counter = 0;
	if (from.row == 0) {
		if (from.col == 0)
			CheckRow(from, counter, 1, 1);
		else if (from.col == board->boardInfo.dimension)
			CheckRow(from, counter, 1, 0);
		else {
			if (to.col == from.col) CheckRow(from, counter, 1, 0);
			else CheckRow(from, counter, 1, 1);
		}
	}
	else if (from.row == board->boardInfo.dimension) {
		if (from.col == 0)
			CheckRow(from, counter, 0, 1);
		else if (from.col == board->boardInfo.dimension * 2)
			CheckRow(from, counter, 0, -1);
	}
	else if (from.row == board->boardInfo.dimension * 2) {
		if (from.col == board->boardInfo.dimension)
			CheckRow(from, counter, -1, 0);
		else if (from.col == board->boardInfo.dimension * 2) 
			CheckRow(from, counter, -1, -1);
		else {
			if (to.col == from.col) CheckRow(from, counter, -1, 0);
			else CheckRow(from, counter, -1, -1);
		}
	}
	else {
		if (from.col < board->boardInfo.dimension) {
			if (from.row == to.row) CheckRow(from, counter, 0, 1);
			else CheckRow(from, counter, -1, 0);
		}
		else {
			if (from.row == to.row) CheckRow(from, counter, 0, -1);
			else CheckRow(from, counter, 1, 0);
		}
	}
	if (!counter) {
		Logger::Log(BAD_MOVE_ROW_IS_FULL);
		return false;
	}
	return true;
}

void Validator::CheckRow(const Board::Position from, int& counter, int rowOffset, int colOffset) const {
	for (int i = 0; i < board->boardInfo.dimension * 2 - 1; i++) {
		if (board->board[from.row + rowOffset + i * rowOffset][from.col + colOffset + i * colOffset] == '_') {
			counter++;
			break;
		}
	}
}

int Validator::FindChains(bool collectPawns) const {
	int chains = 0;
	int visitedSize = board->boardInfo.dimension * 2 + 1;
	Board::Visited** visited = new Board::Visited * [visitedSize];
	for (int i = 0; i < visitedSize; i++)
		visited[i] = new Board::Visited[visitedSize];
	

	for (int row = 1; row < board->boardInfo.dimension * 2; row++) {
		for (int col = 1; col < board->boardInfo.dimension * 2; col++) {
			char field = board->board[row][col];
			if (field != 'W' && field != 'B') continue;
			std::vector<Board::Position> neigbors = DiffNeighb({ row, col }, field);
			if (!neigbors.size()) continue;

			for (int i = 0; i < 3; i++)
				visited[row][col].visitDirection[i] = true;

			for (auto& dirPosition : neigbors) {
				if (dirPosition.row == row - 1) {
					if (dirPosition.col == col) {
						if (CheckChain(visited, { row + 1, col }, 1, 0, board->board[row][col], collectPawns)) chains++;
					}
					else if (CheckChain(visited, { row + 1, col + 1}, 1, 1, board->board[row][col], collectPawns)) chains++;
				}
				else if (dirPosition.row == row + 1) {
					if (dirPosition.col == col) {
						if (CheckChain(visited, { row - 1, col }, -1, 0, board->board[row][col], collectPawns)) chains++;
					}
					else if (CheckChain(visited, { row - 1, col + 1}, -1, -1, board->board[row][col], collectPawns)) chains++;
				}
				else if (dirPosition.col == col - 1) {
					if (CheckChain(visited, { row, col + 1 }, 0, 1, board->board[row][col], collectPawns)) chains++;
				}
				else if (CheckChain(visited, { row, col - 1 }, 0, -1, board->board[row][col], collectPawns)) chains++;
			}
		}
	}
	
	for (int i = 0; i < visitedSize; i++)
		delete[] visited[i];
	delete[] visited;

	return chains;
}

std::vector<Board::Position> Validator::DiffNeighb(const Board::Position& position, char player) const {
	std::vector<Board::Position> neighbors;
	AddNeighbIfDiff(neighbors, position.row + 1, position.col, player);
	AddNeighbIfDiff(neighbors, position.row - 1, position.col, player);
	AddNeighbIfDiff(neighbors, position.row, position.col + 1, player);
	AddNeighbIfDiff(neighbors, position.row, position.col - 1, player);
	AddNeighbIfDiff(neighbors, position.row + 1, position.col + 1, player);
	AddNeighbIfDiff(neighbors, position.row - 1, position.col - 1, player);
	return neighbors;
}

bool Validator::CheckChain(Board::Visited**& visited, const Board::Position& position, int rowOffset, int colOffset, char player, bool collectPawns) const {
	int target = board->boardInfo.pawnsToCapture;
	int visitedCounter = 1;
	int chainSize = 1;

	Directions direction;
	FillDirections(direction, rowOffset, colOffset);

	int row, col, i;
	char field;
	for (i = 0; ; i++) {
		row = position.row + i * rowOffset;
		col = position.col + i * colOffset;
		field = board->board[row][col];
		if (field != player) break;

		visitedCounter += (int)visited[row][col].visitDirection[direction];
		if (visitedCounter >= target) return false;

		visited[row][col].visitDirection[direction] = true;
		chainSize++;
	}

	if (chainSize >= target && collectPawns)
		CollectPawns(i, position, rowOffset, colOffset, player);

	return chainSize >= target;
}

void Validator::FillDirections(Directions& direction, int rowOffset, int colOffset) const {
	if (rowOffset == -1 || rowOffset == 1) {
		if (colOffset == -1 || colOffset == 1) direction = SLANT;
		else direction = HORIZONTAL;
	}
	else direction = VERTICAL;
}

void Validator::AddNeighbIfDiff(std::vector<Board::Position>& neighb, const int& row, const int& col, const char& player) const {
	if (board->board[row][col] &&
		board->board[row][col] != player)
		neighb.push_back({ row, col });
}

void Validator::CollectPawns(int i, const Board::Position& position, int rowOffset, int colOffset, char player) const{
	int row = position.row + i * rowOffset;
	int col = position.col + i * colOffset;
	char field = board->board[row][col];

	for (i; field != '_' && field != '+'; i++) {
		row = position.row + i * rowOffset;
		col = position.col + i * colOffset;
		field = board->board[row][col];
	}

	row = position.row + --i * rowOffset;
	col = position.col + i * colOffset;
	field = board->board[row][col];
	if (field == '+' || field == '_') i--;

	for (i; ; i--) {
		row = position.row + i * rowOffset;
		col = position.col + i * colOffset;
		field = board->board[row][col];
		if (field == '+' || field == '_') break;
		if (field == player)
			board->boardInfo.reserve[player == 'W' ? WHITE : BLACK]++;
		board->board[row][col] = '_';
	}
}

bool Validator::OnTheSameRow(const Board::Position& pos1, const Board::Position& pos2) const{
	return (pos1.col == pos2.col ||
		pos1.row == pos2.row ||
		(pos1.col - pos1.row) == (pos2.col - pos2.row));
}

bool Validator::ValidateMoveExtend() const {
	char player = board->move.pawnCollectInfo.color;
	if (!OnTheSameRow(board->move.pawnCollectInfo.fPosition, board->move.pawnCollectInfo.tPosition)) {
		Logger::Log(WRONG_INDEX_OF_CHOSEN_ROW);
		return false;
	}
	switch (ChainBetween(board->move.pawnCollectInfo.fPosition, board->move.pawnCollectInfo.tPosition, player)) {
	case 2:
		Logger::Log(WRONG_COLOR_OF_CHOSEN_ROW);
		return false;
	case 1:
		Logger::Log(WRONG_INDEX_OF_CHOSEN_ROW);
		return false;
	default:
		break;
	}
	int row1, row2, col1, col2;
	row1 = board->move.pawnCollectInfo.fPosition.row;
	row2 = board->move.pawnCollectInfo.tPosition.row;
	col1 = board->move.pawnCollectInfo.fPosition.col;
	col2 = board->move.pawnCollectInfo.tPosition.col;

	CollectPawns(0, { row1, col1 }, row1 == row2 ? 0 : 1, col1 == col2 ? 0 : 1, player);
	return true;
}

// TODO: do poprawy
int Validator::ChainBetween(const Board::Position& pos1, const Board::Position& pos2, char player) const {
	int chainCounter = 1;
	int row, rowTarget, col, colTarget;
	if (pos1.col == pos2.col) {
		col = pos1.col;
		if (pos1.row < pos2.row) {
			row = pos1.row;
			rowTarget = pos2.row;
		}
		else {
			row = pos2.row;
			rowTarget = pos1.row;
		}
		while (row != rowTarget) {
			if (board->board[row][col] != player) return 2;
			chainCounter++;
			row++;
		}
	}
	else if (pos1.row == pos2.row) {
		row = pos1.row;
		if (pos1.col < pos2.col) {
			col = pos1.col;
			colTarget = pos2.col;
		}
		else {
			col = pos2.col;
			colTarget = pos1.col;
		}
		while (col != colTarget) {
			if (board->board[row][col] != player) return 2;
			chainCounter++;
			row++;
		}
	}
	else {
		if (pos1.row < pos2.row) {
			if (pos1.col < pos2.col) {
				col = pos1.col;
				row = pos1.row;
				colTarget = pos2.col;

				while (col != colTarget) {
					if (board->board[row][col] != player) return 2;
					chainCounter++;
					row++;
					col++;
				}
			}
			else {
				col = pos1.col;
				row = pos1.row;
				colTarget = pos2.col;
				while (col != colTarget) {
					if (board->board[row][col] != player) return 2;
					chainCounter++;
					row++;
					col--;
				}
			}

		}
		else {
			if (pos1.col < pos2.col) {
				col = pos2.col;
				row = pos2.row;
				colTarget = pos1.col;
				while (col != colTarget) {
					if (board->board[row][col] != player) return 2;
					chainCounter++;
					row++;
					col--;
				}
			}
			else {
				col = pos2.col;
				row = pos2.row;
				colTarget = pos1.col;

				while (col != colTarget) {
					if (board->board[row][col] != player) return 2;
					chainCounter++;
					row++;
					col++;
				}
			}
		}
	}
	if (chainCounter < board->boardInfo.pawnsToCapture) return 1;
	return 0;
}