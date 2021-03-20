//
// Created by Denis Afendikov on 17.03.2021.
//

#ifndef _PARSER_H_
#define _PARSER_H_

#include "../lexer/Lexer.h"

using CurrentToken = std::vector<Lexer::LineToken>::const_iterator;

class Parser
{
	CurrentToken _currToken{};
	std::vector<Lexer::LineToken> _tokens;
	std::vector<std::string> _identifiers;

  public:
	Parser();

	bool parse(const std::vector<Lexer::LineToken>& tokens, const std::vector<std::string>& identifiers);

	bool parseProgram();

	bool parseToken(Token::Type type);
	bool parseKeyword(const std::string& keyword);


};

#endif //_PARSER_H_
