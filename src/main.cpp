#include <iostream>
#include <fstream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"


int main() {
	std::ifstream inputFile{ "test.jlang" };
	Lexer lexer{};
	lexer.lex(inputFile);
	lexer.printTokenTable();
	std::cout << "Lexer success status: " << lexer.isLastLexSuccess << std::endl;

	if(!lexer.isLastLexSuccess) {
		std::cerr << "Lexer error" << std::endl;
		exit(1);
	}

	Parser parser{};
	parser.parse(lexer.getTokens(), lexer.getIdentifiers());

	return 0;
}
