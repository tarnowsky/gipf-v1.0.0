#pragma once
enum Commands {
	LOAD_GAME_BOARD,
	PRINT_GAME_BOARD,
	DO_MOVE,
};

enum PawnColors {
	WHITE,
	BLACK,
};

enum ReturnLogs {
	// test 0
	BOARD_STATE_OK,
	WRONG_WHITE_PAWNS_NUMBER,
	WRONG_BLACK_PAWNS_NUMBER,
	WRONG_BOARD_ROW_LENGTH,

	// test 1
	EMPTY_BOARD,

	// test 2
	MOVE_COMMITTED,
	BAD_MOVE_WRONG_INDEX,
	UNKNOWN_MOVE_DIRECTION,
	BAD_MOVE_WRONG_STARTING_FIELD,
	BAD_MOVE_WRONG_DESTINATION_FIELD,
	BAD_MOVE_ROW_IS_FULL,

	// test 3
	ERROR_FOUND_ROW_OF_LENGTH_K,

	//test 5
	WRONG_COLOR_OF_CHOSEN_ROW,
	WRONG_INDEX_OF_CHOSEN_ROW,
};

enum Directions {
	HORIZONTAL,
	VERTICAL,
	SLANT,
};