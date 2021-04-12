//
// Created by Denis Afendikov on 12.04.2021.
//

#include "IdentifierToken.h"
#include "../rpn_interpreter/exceptions/RunTimeError.h"


IdentifierToken::IdentifierToken( const std::string& lexeme, unsigned int id ) :
	Token(Token::Type::Identifier, lexeme),
	_id(id),
	_identifierType(UNDEFINED),
	_value() {}

void IdentifierToken::setIdentifierType( IdentifierToken::Type type ) {
	if (this->_identifierType != UNDEFINED) {
		throw RunTimeError{ "Variable already declared" };
	}
	this->_identifierType = type;
}
