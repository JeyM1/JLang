//
// Created by Denis Afendikov on 27.02.2021.
//

#ifndef _LEXER_H_
#define _LEXER_H_

#include <map>
#include <vector>
#include <functional>
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

	struct LineToken
	{
		Token token;
		unsigned int line;

		explicit LineToken( unsigned int, Token token );
	};

	static const std::map<std::pair<unsigned int, ClassOfChar>, unsigned int> stateTransitionFn;
	static const unsigned int initialState{ 0 };
	static const std::map<
		unsigned int,
		std::function<void( std::istream&, const std::string&, char, unsigned int, Lexer& )>
	> finalStateProcessingFunctions;

	std::vector<LineToken> tokens;
	std::vector<std::string> identifiers;

  public:
	Lexer();

	bool lex( std::istream& ) noexcept;
	static ClassOfChar classOfChar( char );
	void printTokenTable();

};

#endif //_LEXER_H_
