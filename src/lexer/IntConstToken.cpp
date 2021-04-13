//
// Created by Denis Afendikov on 02.03.2021.
//

#include "IntConstToken.h"


IntConstToken::IntConstToken( const std::string& lexeme )
	: Token(Type::IntConst, lexeme) {
	try {
		this->_actual = std::make_shared<CTYPE>(std::stoi(lexeme));
	}
	catch (...) {
		// TODO: generate error
		this->_type = Unexpected;
		std::cerr << "Unexpected IntConst" << std::endl;
	}

}

IntConstToken::IntConstToken( const CTYPE& actual ) :
	Token(Token::Type::IntConst, std::to_string(actual)),
	_actual(std::make_shared<CTYPE>(actual)) {}

