#include "Logger.h"

void Logger::Log(ReturnLogs returnLog) {
	switch (returnLog) {
	case BOARD_STATE_OK:
		std::cout << "BOARD_STATE_OK";
		break;
	case WRONG_WHITE_PAWNS_NUMBER:
		std::cout << "WRONG_WHITE_PAWNS_NUMBER";
		break;
	case WRONG_BLACK_PAWNS_NUMBER:
		std::cout << "WRONG_BLACK_PAWNS_NUMBER";
		break;
	case WRONG_BOARD_ROW_LENGTH:
		std::cout << "WRONG_BOARD_ROW_LENGTH";
		break;
	case MOVE_COMMITTED:
		std::cout << "MOVE_COMMITTED";
		break;
	case UNKNOWN_MOVE_DIRECTION:
		std::cout << "UNKNOWN_MOVE_DIRECTION";
		break;
	case BAD_MOVE_ROW_IS_FULL:
		std::cout << "BAD_MOVE_ROW_IS_FULL";
		break;
	case EMPTY_BOARD:
		std::cout << "EMPTY_BOARD";
		break;
	default:
		std::cout << "Error. Return log not found.";
	}
	std::cout << std::endl;
}

void Logger::LogWithField(ReturnLogs returnLog, const std::string& field) {
	switch (returnLog) {
	case BAD_MOVE_WRONG_INDEX:
		std::cout << "BAD_MOVE_";
		for (auto& i : field)
			std::cout << i;
		std::cout << "_IS_WRONG_INDEX";
		break;
	case BAD_MOVE_WRONG_STARTING_FIELD:
		std::cout << "BAD_MOVE_";
		for (auto& i : field)
			std::cout << i; 
		std::cout << "_IS_WRONG_STARTING_FIELD";
		break;
	case BAD_MOVE_WRONG_DESTINATION_FIELD:
		std::cout << "BAD_MOVE_";
		for (auto& i : field)
			std::cout << i;
		std::cout << "_IS_WRONG_DESTINATION_FIELD";
		break;
	default:
		std::cout << "Error. Return log not found.";
	}
	std::cout << std::endl;
}

void Logger::LogWithNum(ReturnLogs returnLog, int num){
	switch (returnLog) {
	case ERROR_FOUND_ROW_OF_LENGTH_K:
		std::cout << "ERROR_FOUND_" << num;
		if (num == 1) std::cout << "_ROW_OF_LENGTH_K";
		else std::cout << "_ROWS_OF_LENGTH_K";
		break;
	default:
		std::cout << "Error. Return log not found.";
	}
	std::cout << std::endl;
}
