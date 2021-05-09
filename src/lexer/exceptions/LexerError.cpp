//
// Created by Denis Afendikov on 27.04.2021.
//

#include "LexerError.h"


LexerError::LexerError( const std::string& message ) :
	_message(std::move("LexerError: " + message)) {}

const char* LexerError::what() const noexcept {
	return _message.c_str();
}