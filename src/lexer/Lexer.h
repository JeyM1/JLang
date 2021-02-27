//
// Created by Denis Afendikov on 27.02.2021.
//

#ifndef _LEXER_H_
#define _LEXER_H_

#include <map>
#include <vector>
#include "Token.h"

class Lexer
{
  public:
	enum ClassOfChar
	{
		Letter,
		Digit,
		Whitespace,
		Newline,

		Other
	};

	struct LineToken {
		Token token;
		unsigned int line{};

		LineToken( const Token& token );
	};

	static const std::map<std::string, Token::Type> languageTokens;

  protected:
	std::vector<LineToken> _tokens;
	std::map<std::string_view, int> _identifierIds;

  public:
	Lexer();

	void lex(std::istream&) noexcept;



};

#endif //_LEXER_H_
