#include "Giph.h"

int main() {
	Giph giph;
	Board::Position p;
	p = giph.FieldDecoder("f8", 5);
	std::cout << p.row << ", " << p.col << std::endl;
	std::cin.get();
	//giph.Start();
}

