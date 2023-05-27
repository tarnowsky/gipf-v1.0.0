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
	}
	std::cout << std::endl;
}