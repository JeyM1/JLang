//
// Created by Denis Afendikov on 02.03.2021.
//

#include "RealConstToken.h"


RealConstToken::RealConstToken( const std::string& lexeme ) : Token(Type::RealConst, lexeme) {
	try {
		this->_actual = std::stold(lexeme);
	}
	catch (...) {
		// TODO: generate error
		this->_type = Unexpected;
		std::cerr << "Unexpected RealConst" << std::endl;
	}
}
