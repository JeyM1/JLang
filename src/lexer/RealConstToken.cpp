//
// Created by Denis Afendikov on 02.03.2021.
//

#include "RealConstToken.h"
#include "exceptions/LexerError.h"


RealConstToken::RealConstToken( const std::string& lexeme ) : Token(Type::RealConst, lexeme) {
	try {
		this->_actual = std::make_shared<CTYPE>(std::stold(lexeme));
	}
	catch (...) {
		this->_type = Unexpected;
		throw LexerError{ "Unexpected RealConst" };
	}
}

RealConstToken::RealConstToken( const CTYPE& actual ) :
	Token(Token::Type::BoolConst, std::to_string(actual)),
	_actual(std::make_shared<CTYPE>(actual)) {}