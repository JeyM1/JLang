//
// Created by Denis Afendikov on 12.04.2021.
//

#include <iomanip>
#include "RPNInterpreter.h"
#include "exceptions/RunTimeError.h"


bool RPNInterpreter::interpret( const std::vector<Lexer::LineToken>& tokens,
                                const std::vector<std::shared_ptr<IdentifierToken>>& identifiers ) {
	this->_currToken = tokens.begin();
	this->_tokens = tokens;
	this->_identifiers = identifiers;
	try {
		return true;
	}
	catch (const RunTimeError& error) {
		std::cerr << error.what() << std::endl;
		if (_currToken != _tokens.end()) {
			std::cerr << "\t\t at " << std::setw(3) << _currToken->line
			          << " | \"" << _currToken->token->lexeme() << "\"" << std::endl;
		}
		return false;
	}
}
