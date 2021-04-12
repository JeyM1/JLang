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

	if (!lexer.isLastLexSuccess) {
		std::cerr << "Lexer error" << std::endl;
		exit(1);
	}

	Parser parser{};
	if (parser.parse(lexer.getTokens(), lexer.getIdentifiers())) {
		std::cout << "Parser success status: 1" << std::endl;
	}
	else {
		std::cerr << "Parser error" << std::endl;
		exit(1);
	}

	auto tokens = parser.getParsedTokens();
	for(auto token : tokens) {
		std::cout << token->lexeme() << " ";
	}
	std::cout << std::endl;

	return 0;
}
