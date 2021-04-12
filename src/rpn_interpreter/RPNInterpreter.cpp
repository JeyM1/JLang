//
// Created by Denis Afendikov on 12.04.2021.
//

#include "RPNInterpreter.h"


bool RPNInterpreter::interpret( std::vector<Lexer::LineToken> tokens ) {
	bool isSuccess = true;
	this->_currToken = tokens.begin();
	return isSuccess;
}
