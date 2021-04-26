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
	std::vector<std::shared_ptr<IdentifierToken>> _identifiers;

	static const std::vector<std::string> _types;

	std::vector<Lexer::LineToken> postfixTokens;

  public:
	Parser();

	const std::vector<Lexer::LineToken>& getParsedTokens() const {
		return postfixTokens;
	}

	const std::vector<std::shared_ptr<IdentifierToken>>& getIdentifiers() const {
		return _identifiers;
	}

	bool
	parse( const std::vector<Lexer::LineToken>& tokens, const std::vector<std::shared_ptr<IdentifierToken>>& identifiers );

	bool parseProgram();

	bool parseToken( Token::Type type );
	bool parseIdentifierById( unsigned int id );
	bool parseIdentifier();
	bool parseKeyword( const std::string& keyword );

	bool parseStatementList();
	bool parseStatement();
	bool parseExpression();
	bool parseInitialization();
	bool parseIdentDecl( const Lexer::LineToken& );
	bool parseInp();
	bool parseOut();
	bool parseIdentList( const Lexer::LineToken& insertToken );
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
