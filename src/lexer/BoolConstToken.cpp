//
// Created by Denis Afendikov on 02.03.2021.
//

#include <iostream>
#include "BoolConstToken.h"


BoolConstToken::BoolConstToken( const std::string& lexeme )
	: Token(Token::Type::BoolConst, lexeme) {
	if (lexeme == "true") {
		_actual = std::make_shared<CTYPE>(true);
	}
	else if (lexeme == "false") {
		_actual = std::make_shared<CTYPE>(false);
	}
	else {
		std::cerr << "Unexpected BoolConstToken, got \"" << lexeme << "\"." << std::endl;
	}
}

BoolConstToken::BoolConstToken( const BoolConstToken::CTYPE& actual ) :
	Token(Token::Type::BoolConst, std::to_string(actual)),
	_actual(std::make_shared<CTYPE>(actual)) {}
