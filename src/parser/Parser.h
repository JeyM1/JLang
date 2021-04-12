//
// Created by Denis Afendikov on 17.03.2021.
//

#ifndef _PARSER_H_
#define _PARSER_H_

#include "../lexer/Lexer.h"
#include "tree/Tree.h"


using CurrentToken = std::vector<Lexer::LineToken>::const_iterator;

class Parser
{
	CurrentToken _currToken{};
	std::vector<Lexer::LineToken> _tokens;
	std::vector<std::string> _identifiers;
	std::vector<std::string> _declaredIdentifiers;

	static const std::vector<std::string> _types;

	std::vector<std::shared_ptr<Token>> postfixTokens;

  public:
	Parser();

	const std::vector<std::shared_ptr<Token>>& getParsedTokens() const {
		return postfixTokens;
	}

	bool parse(const std::vector<Lexer::LineToken>& tokens, const std::vector<std::string>& identifiers);

	bool parseProgram();

	bool parseToken(Token::Type type);
	bool parseIdentifierById( unsigned int id);
	bool parseIdentifier();
	bool parseKeyword(const std::string& keyword);

	bool parseStatementList();
	bool parseStatement();
	bool parseExpression();
	bool parseInitialization();
	bool parseIdentDecl(const std::shared_ptr<Token>&);
	bool parseInp();
	bool parseOut();
	bool parseIdentList();
	bool parseTerm();
	bool parseFactor();
	bool parseFirstExpr();
	bool parseIfStatement();
	bool parseBoolExpr();
	bool parseBoolTerm();
	bool parseBoolFactor();
	bool parseBoolRelation();
	bool parseDoBlock();
	bool parseForStatement();
	bool parseType();
	bool parseAssign();
};

#endif //_PARSER_H_
