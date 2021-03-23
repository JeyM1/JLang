//
// Created by Denis Afendikov on 17.03.2021.
//

#include "Parser.h"
#include "exceptions/SyntaxError.h"
#include <iostream>
#include <iomanip>
#include "../logger.h"


Parser::Parser() {}

const std::vector<std::string> Parser::_types = { "int", "real", "bool" };

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

	parseKeyword("program");
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
	if (token->is_not(Token::Keyword) || token->lexeme() != keyword) {
		throw SyntaxError{
			"Expected keyword \"" + keyword + "\", got \"" + token->lexeme() +
			"\" instead."
		};
	}
	++this->_currToken;

	return true;
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

	return true;
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
		parseToken(Token::Semicolon);
		break;
	}
	case Token::Keyword: {
		// Inp, Out or Initialization
		if (_currToken->token->lexeme() == "print") {
			parseOut();
			parseToken(Token::Semicolon);
		}
		else if (_currToken->token->lexeme() == "read") {
			parseInp();
			parseToken(Token::Semicolon);
		}
		else if (_currToken->token->lexeme() == "if") {
			parseIfStatement();
		}
		else if (_currToken->token->lexeme() == "for") {
			parseForStatement();
		}
		else {
			parseInitialization();
			parseToken(Token::Semicolon);
		}
		break;
	}
	case Token::RightCurly: {
		// end of program
		return false;
	}
	}
	return true;
}

bool Parser::parseExpression() {
	// [Sign]
	if (_currToken->token->is_one_of(Token::Add, Token::Sub)) {
		// TODO: set sign somewhere
		++_currToken;
	}
	// Term
	parseTerm();
	// { AddOp Term }
	while (_currToken->token->is_one_of(Token::Add, Token::Sub)) {
		++_currToken;
		parseExpression();
	}
	return true;
}

bool Parser::parseTerm() {
	parseFactor();
	while (_currToken->token->is_one_of(Token::Multiply, Token::Division, Token::IntDivision)) {
		++_currToken;
		parseExpression();
	}
	return true;
}

bool Parser::parseFactor() {
	parseFirstExpr();
	while (_currToken->token->is(Token::Power)) {
		++_currToken;
		parseExpression();
	}
	return true;
}

bool Parser::parseFirstExpr() {
	if (_currToken->token->is_one_of(Token::IntConst, Token::RealConst, Token::BoolConst, Token::Identifier)) {
		++_currToken;
	}
	else if (_currToken->token->is(Token::LeftParen)) {
		parseToken(Token::LeftParen);
		parseExpression();
		parseToken(Token::RightParen);
	}
	else {
		throw SyntaxError{ "Expected const, ident or Expression" };
	}
	return true;
}

bool Parser::parseType() {
	if (std::find(_types.begin(), _types.end(), _currToken->token->lexeme()) == _types.end()) {
		// token is not Type
		throw SyntaxError{ "Expected type in Initialization; got \"" + _currToken->token->lexeme() + "\" instead." };
	}
	++_currToken;
	return true;
}

bool Parser::parseInitialization() {
	parseType();
	parseIdentDecl();
	while (_currToken->token->is(Token::Comma)) {
		++_currToken;
		parseIdentDecl();
	}
	return true;
}

bool Parser::parseIdentDecl() {
	parseIdentifier();
	parseToken(Token::Assign);
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

bool Parser::parseBoolExpr() {
	parseBoolTerm();
	while (_currToken->token->is(Token::Or)) {
		++_currToken;
		parseBoolTerm();
	}
	return true;
}

bool Parser::parseBoolTerm() {
	parseBoolFactor();
	while (_currToken->token->is(Token::And)) {
		++_currToken;
		parseBoolFactor();
	}
	return true;
}

bool Parser::parseBoolFactor() {
	if (_currToken->token->is(Token::Not)) {
		++_currToken;
		// TODO: do something with NOT
		parseBoolFactor();
	}
	else if (_currToken->token->is(Token::LeftParen)) {
		parseToken(Token::LeftParen);
		parseBoolTerm();
		parseToken(Token::RightParen);
	}
//	else if (
//		_currToken->token->is_one_of(Token::Identifier, Token::BoolConst) &&
//		std::next(_currToken) != _tokens.end() &&
//		!std::next(_currToken)->token->is_one_of(
//			Token::LessThan,
//			Token::LessOrEqualTo,
//			Token::EqualTo,
//			Token::NotEqual,
//			Token::GreaterOrEqualTo,
//			Token::GreaterThan
//		)) {
//		++_currToken;
//	}
	else {
		parseBoolRelation();
	}

	return true;
}

bool Parser::parseBoolRelation() {
	parseExpression();
	if (_currToken->token->is_one_of(
		Token::LessThan,
		Token::LessOrEqualTo,
		Token::EqualTo,
		Token::NotEqual,
		Token::GreaterOrEqualTo,
		Token::GreaterThan)
		) {
		++_currToken;
		parseExpression();
	}

//	if (!_currToken->token->is_one_of(
//		Token::LessThan,
//		Token::LessOrEqualTo,
//		Token::EqualTo,
//		Token::NotEqual,
//		Token::GreaterOrEqualTo,
//		Token::GreaterThan)
//		) {
//		throw SyntaxError{ "Expected RelationOperator in BoolRelation." };
//	}
//	++_currToken;
//	parseExpression();
	return true;
}

bool Parser::parseDoBlock() {
	if (_currToken->token->is(Token::LeftCurly)) {
		// StatementList
		parseToken(Token::LeftCurly);
		parseStatementList();
		parseToken(Token::RightCurly);
	}
	else {
		// Statement only
		parseStatement();
	}

	return true;
}

bool Parser::parseIfStatement() {
	parseKeyword("if");
	parseToken(Token::LeftParen);
	parseBoolExpr();
	parseToken(Token::RightParen);
	parseKeyword("then");
	parseDoBlock();
	if (_currToken->token->is(Token::Keyword) && _currToken->token->lexeme() == "else") {
		parseKeyword("else");
		parseDoBlock();
	}
	return true;
}

bool Parser::parseForStatement() {
	parseKeyword("for");
	parseToken(Token::LeftParen);
	// IndExpr
	parseInitialization();
	parseKeyword("by");
	parseExpression();
	parseKeyword("while");
	parseBoolExpr();
	parseToken(Token::RightParen);
	parseKeyword("do");
	parseDoBlock();
	return true;
}


