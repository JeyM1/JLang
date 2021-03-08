#include <iostream>
#include <fstream>
#include "lexer/Lexer.h"


int main() {
	std::ifstream inputFile{ "test.jlang" };
	Lexer lexer{};
	lexer.lex(inputFile);
	lexer.printTokenTable();
	std::cout << "Lexer success status: " << lexer.isLastLexSuccess << std::endl;
	return 0;
}
