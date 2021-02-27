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
	static const std::map<ClassOfChar, std::string> charClasses;

	struct LineToken {
		Token token;
		unsigned int line{};

		LineToken( const Token& token );
	};

	static const std::map<std::string, Token::Type> languageTokens;
	static const std::map<std::pair<unsigned int, ClassOfChar>, unsigned int> stateTransitionFn;
	static const unsigned int initialState{0};

  protected:
	std::vector<LineToken> _tokens;
	std::map<std::string_view, int> _identifierIds;

  public:
	Lexer();

	void lex(std::istream&) noexcept;
	static ClassOfChar classOfChar(char);


};

#endif //_LEXER_H_
