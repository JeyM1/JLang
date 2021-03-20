//
// Created by Denis Afendikov on 18.03.2021.
//

#include "SyntaxError.h"

#include <utility>


SyntaxError::SyntaxError( const unsigned int line, const std::string& message ) :
	_line(line),
	_message(std::move("SyntaxError (line" + std::to_string(_line) + "):" + message)) {}

const char* SyntaxError::what() const noexcept {
	return _message.c_str();
}