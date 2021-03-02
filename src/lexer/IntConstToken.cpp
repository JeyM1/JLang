//
// Created by Denis Afendikov on 02.03.2021.
//

#include "IntConstToken.h"
IntConstToken::IntConstToken( const std::string& lexeme )
	: Token(Type::IntConst, lexeme) {
	try {
		this->_actual = std::stoi(lexeme);
	}
	catch (...) {
		// TODO: generate error
		this->_type = Unexpected;
		std::cerr << "Unexpected IntConst" << std::endl;
	}

}
