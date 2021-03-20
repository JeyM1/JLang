//
// Created by Denis Afendikov on 17.03.2021.
//

#include "Parser.h"
#include "exceptions/SyntaxError.h"
#include <iostream>
#include "../logger.h"


Parser::Parser() {}

bool Parser::parse( const std::vector<Lexer::LineToken>& tokens, const std::vector<std::string>& identifiers ) {
	this->_currToken = tokens.begin();
	this->_tokens = tokens;
	this->_identifiers = identifiers;


	return this->parseProgram();
}

bool Parser::parseProgram() {


	parseKeyword("program");



}

bool Parser::parseKeyword( const std::string& keyword ) {
	if(this->_currToken == this->_tokens.end()) {
		throw SyntaxError{0, "Unexpected end of program"};
	}

	if(this->_currToken->token->is(Token::Keyword) && this->_currToken->token->lexeme() == keyword){
		log("Parser: ") << "[line " << "] " << "Found Keyword " + keyword << std::endl;
		return true;
	}
	return false;
}

