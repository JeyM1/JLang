//
// Created by Denis Afendikov on 02.03.2021.
//

#include "RealConstToken.h"


RealConstToken::RealConstToken( const std::string& lexeme ) : Token(Type::RealConst, lexeme) {
	try {
		this->_actual = std::make_shared<CTYPE>(std::stold(lexeme));
	}
	catch (...) {
		// TODO: generate error
		this->_type = Unexpected;
		std::cerr << "Unexpected RealConst" << std::endl;
	}
}

RealConstToken::RealConstToken( const CTYPE& actual ) :
	Token(Token::Type::BoolConst, std::to_string(actual)),
	_actual(std::make_shared<CTYPE>(actual)) {}