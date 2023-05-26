#include "Parser.h"

int main() {
	Parser parser;
	while (parser.ParseCommand()) {
		parser.LogBoardStateInfo();
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