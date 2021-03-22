//
// Created by Denis Afendikov on 17.03.2021.
//

#include "Parser.h"
#include "exceptions/SyntaxError.h"
#include <iostream>
#include <iomanip>
#include "../logger.h"


Parser::Parser() {}

const std::vector<std::string> Parser::_types = {"int", "real", "bool"};

bool Parser::parse( const std::vector<Lexer::LineToken>& tokens, const std::vector<std::string>& identifiers ) {
	this->_currToken = tokens.begin();
	this->_tokens = tokens;
	this->_identifiers = identifiers;
	try {
		return this->parseProgram();
	}
	catch (const SyntaxError& error) {
		std::cerr << error.what() << std::endl;
		if (_currToken != _tokens.end()) {
			std::cerr << "\t\t at " << std::setw(3) << _currToken->line
			          << " | \"" << _currToken->token->lexeme() << "\"" << std::endl;
		}
		return false;
	}
}

bool Parser::parseProgram() {

	if (!parseKeyword("program")) {
		throw SyntaxError{ "Program must start with \"program\" keyword." };
	}
	parseIdentifierById(0);
	parseToken(Token::LeftCurly);
	parseStatementList();
	parseToken(Token::RightCurly);

	return true;
}

bool Parser::parseKeyword( const std::string& keyword ) {
	if (this->_currToken == this->_tokens.end()) {
		throw SyntaxError{ "Unexpected end of program" };
	}

	std::shared_ptr<Token> token = this->_currToken->token;
	++this->_currToken;

	return token->is(Token::Keyword) && token->lexeme() == keyword;
}

bool Parser::parseIdentifierById( unsigned int id ) {
	if (this->_currToken == this->_tokens.end()) {
		throw SyntaxError{ "Unexpected end of program" };
	}

	std::shared_ptr<Token> token = this->_currToken->token;
	if (token->is_not(Token::Identifier)) {
		throw SyntaxError{ "Expected identifier, got " + std::to_string(token->type()) };
	}
	++this->_currToken;

	return _identifiers.at(id) == token->lexeme();
}

bool Parser::parseIdentifier() {
	if (this->_currToken == this->_tokens.end()) {
		throw SyntaxError{ "Unexpected end of program" };
	}

	std::shared_ptr<Token> token = this->_currToken->token;
	if (token->is_not(Token::Identifier)) {
		throw SyntaxError{ "Expected identifier, got " + std::to_string(token->type()) };
	}
//	if (std::find(_declaredIdentifiers.begin(),
//		_declaredIdentifiers.end(),
//		token->lexeme()) == _declaredIdentifiers.end()) {
//		throw SyntaxError{ "Undeclared variable " + token->lexeme() };
//	}

	++this->_currToken;

	return true;
}

bool Parser::parseToken( Token::Type type ) {
	if (this->_currToken == this->_tokens.end()) {
		throw SyntaxError{ "Unexpected end of program" };
	}

	std::shared_ptr<Token> token = this->_currToken->token;
	if (token->is_not(type)) {
		throw SyntaxError{ "Expected " + std::to_string(type) + ", got " + std::to_string(token->type()) };
	}
	++this->_currToken;

	return true;
}

bool Parser::parseStatementList() {
	while (parseStatement()) {

	}
	return true;
}

bool Parser::parseStatement() {
	switch (_currToken->token->type()) {
	case Token::Identifier: {
		// Assign
		parseIdentifier();
		parseToken(Token::Assign);
		parseExpression();

	}
	}
	return false;
}

bool Parser::parseExpression() {
	return false;
}

bool Parser::parseDeclaration() {

	if (std::find(_types.begin(), _types.end(), _currToken->token->lexeme()) == _types.end()) {
		// token is not Type
		throw SyntaxError{"Expected type in Declaration; got \"" + _currToken->token->lexeme() + "\" instead."};
	}
	++_currToken;

	parseIdentDecl();

	while (_currToken->token->is(Token::Comma)) {
		++_currToken;
		parseIdentDecl();
	}

	return true;
}

bool Parser::parseIdentDecl() {
	parseIdentifier();
	if(_currToken->token->is_not(Token::Assign)) {
		throw SyntaxError{"Expected \"=\", got \"" + _currToken->token->lexeme() + "\" instead."};
	}
	parseExpression();
	return true;
}

bool Parser::parseInp() {
	parseKeyword("read");
	parseToken(Token::LeftParen);
	parseIdentList();
	parseToken(Token::RightParen);
	return true;
}

bool Parser::parseOut() {
	parseKeyword("print");
	parseToken(Token::LeftParen);
	parseIdentList();
	parseToken(Token::RightParen);
	return true;
}

bool Parser::parseIdentList() {
	parseIdentifier();
	while (_currToken->token->is(Token::Comma)) {
		++_currToken;
		parseIdentifier();
	}
	return true;
}




