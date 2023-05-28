#pragma once
#include "Board.h"
#include "Logger.h"

class Validator {
public:
	explicit Validator(Board* board);
	void ValidateBoard();
	//void ValidateMove() const;
	void ValidateMove(const Board::Move& move) const;
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
};