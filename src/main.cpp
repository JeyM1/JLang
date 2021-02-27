#include <iostream>
#include <fstream>
#include "lexer/Lexer.h"

int main() {
	std::ifstream inputFile{"test.jlang"};
	Lexer lexer{};
	lexer.lex(inputFile);
	return 0;
}
