#include <iostream>
#include <fstream>
#include "lexer/Lexer.h"

int main() {
	std::ifstream inputFile{"test.jlang"};
	Lexer lexer{};
	lexer.lex(inputFile);
	lexer.printTokenTable();
	return 0;
}
