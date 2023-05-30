#pragma once
#include "Board.h"
#include "Logger.h"

class Validator {
public:
	explicit Validator(Board* board);

	void ValidateBoard();

	void ValidateMove() const;
private:
	Board* board;

	bool CheckPawnsInTotal(PawnColors pawnColor) const;
	bool CheckBoardRows();

	static Board::Position FieldDecoder(const std::string& field, int dimension);
	bool ValidateIndex(const Board::Position& position, const std::string& field) const;
	bool ValiateStartingField(const Board::Position& position, const std::string& field) const;
	std::vector<Board::Position> GetPossibleMoves(const Board::Position& position) const;
	bool ValidateDestinationField(const Board::Position& position, const std::string& field) const ;
	bool ValidateMoveDirection(const Board::Position& from, const Board::Position& to) const;
	bool ValidateFullRow(const Board::Position& from, const Board::Position& to) const;
	void CheckRow(const Board::Position from, int& counter, int rowOffset, int colOffset) const;

	int FindChains() const;
	std::vector<Board::Position> DiffNeighb(const Board::Position& position, char player) const;
	void AddNeighbIfDiff(std::vector<Board::Position>& neighb, const int& row, const int& col, const char& player) const;

	bool CheckChain(Board::Visited**& visited, const Board::Position& position, int rowOffset, int colOffset, char player) const;
	void FillDirections(Board::Visited::Directions*& directions, int rowOffset, int colOffset) const;
};