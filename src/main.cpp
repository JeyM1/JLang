#include <iostream>
#include <fstream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "rpn_interpreter/RPNInterpreter.h"


int main() {
	std::ifstream inputFile{ "test.jlang" };
	Lexer lexer{};
	lexer.lex(inputFile);
//	lexer.printTokenTable();
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
	std::cout << "RPN of the code:" << std::endl;
	auto rpn_tokens = parser.getParsedTokens();
	for (const auto& token : rpn_tokens) {
		std::cout << token.token->lexeme() << " ";
	}
	std::cout << std::endl;

	RPNInterpreter interpreter{ parser.getParsedTokens(), parser.getIdentifiers() };
	std::cout << "Program input-output: " << std::endl;
	if (interpreter.interpret()) {
		std::cout << "Interpreter success status: 1" << std::endl;
	}
	else {
		std::cerr << "Interpreter error" << std::endl;
		exit(1);
	}

	std::cout << "Identifiers table: " << std::endl;
	const auto& identifiers = interpreter.getIdentifiers();
	for (const auto& identifier : identifiers) {
		std::cout << *identifier << std::endl;
	}

	return 0;
}
