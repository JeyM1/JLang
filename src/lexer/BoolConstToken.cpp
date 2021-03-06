//
// Created by Denis Afendikov on 02.03.2021.
//

#include <iostream>
#include "BoolConstToken.h"


BoolConstToken::BoolConstToken( const std::string& lexeme )
	: Token(Token::Type::BoolConst, lexeme) {
	if (lexeme == "true") {
		_actual = true;
	}
	else if (lexeme == "false") {
		_actual = false;
	}
	else {
		std::cerr << "Unexpected BoolConstToken, got \"" << lexeme << "\"." << std::endl;
	}

}
