//
// Created by Denis Afendikov on 12.04.2021.
//

#include "IdentifierToken.h"
#include "../rpn_interpreter/exceptions/RunTimeError.h"
#include "BoolConstToken.h"
#include "IntConstToken.h"
#include "RealConstToken.h"


IdentifierToken::IdentifierToken( const std::string& lexeme, unsigned int id ) :
	Token(Token::Type::Identifier, lexeme),
	_id(id),
	_variableType(UNDEFINED),
	_actual() {}

void IdentifierToken::setVariableType( VariableType type ) {
	if (this->_variableType != UNDEFINED) {
		throw RunTimeError{ "Variable already declared" };
	}
	this->_variableType = type;
}

std::shared_ptr<void> IdentifierToken::actual() const {
	if (this->_variableType == UNDEFINED) {
		throw RunTimeError{ "variable \"" + this->_lexeme + "\" is undefined." };
	}
	if (!this->_actual) {
		throw RunTimeError{ "variable \"" + this->_lexeme + "\" is NULL." };
	}
	return _actual;
}

void IdentifierToken::setActual( std::shared_ptr<void> value, VariableType from ) {
	switch (this->_variableType) {
	case INT:
		switch (from) {
		case INT:
			this->_actual = value;
			break;
		case REAL:
			this->_actual = std::make_shared<IntConstToken::CTYPE>((IntConstToken::CTYPE)*std::static_pointer_cast<
				RealConstToken::CTYPE>(value));
			break;
		case BOOL:
			this->_actual = std::make_shared<IntConstToken::CTYPE>((IntConstToken::CTYPE)*std::static_pointer_cast<
				BoolConstToken::CTYPE>(value));
			break;
		case UNDEFINED:
			throw RunTimeError{ "Variable is undefined, cannot setActual!" };
		}
		break;
	case REAL:
		switch (from) {
		case INT:
			this->_actual = std::make_shared<RealConstToken::CTYPE>((RealConstToken::CTYPE)*std::static_pointer_cast<
				IntConstToken::CTYPE>(value));;
			break;
		case REAL:
			this->_actual = value;
			break;
		case BOOL:
			this->_actual = std::make_shared<RealConstToken::CTYPE>((RealConstToken::CTYPE)*std::static_pointer_cast<
				BoolConstToken::CTYPE>(value));
			break;
		case UNDEFINED:
			throw RunTimeError{ "Variable is undefined, cannot setActual!" };
		}
		break;
	case BOOL:
		switch (from) {
		case INT:
			this->_actual = std::make_shared<BoolConstToken::CTYPE>((BoolConstToken::CTYPE)*std::static_pointer_cast<
				IntConstToken::CTYPE>(value));
			break;
		case REAL:
			this->_actual = std::make_shared<BoolConstToken::CTYPE>((BoolConstToken::CTYPE)*std::static_pointer_cast<
				RealConstToken::CTYPE>(value));;
			break;
		case BOOL:
			this->_actual = value;
			break;
		case UNDEFINED:
			throw RunTimeError{ "Variable is undefined, cannot setActual!" };
		}
		break;
	case UNDEFINED:
		throw RunTimeError{ "Variable is undefined, cannot setActual!" };
	}
}

std::ostream& operator<<( std::ostream& os, const IdentifierToken& token ) {
	static const std::map<VariableType, std::string> typeString = {
		{ VariableType::INT, "int" },
		{ VariableType::REAL, "real" },
		{ VariableType::BOOL, "bool" },
		{ VariableType::UNDEFINED, "undefined" },
	};
	os << "| name: " << token._lexeme << " | type: " << typeString.at(token._variableType) << " | actual: ";
	switch (token._variableType) {

	case INT:
		std::cout << std::to_string(*std::static_pointer_cast<IntConstToken::CTYPE>(token._actual));
		break;
	case REAL:
		std::cout << std::to_string(*std::static_pointer_cast<RealConstToken::CTYPE>(token._actual));
		break;
	case BOOL:
		std::cout << std::to_string(*std::static_pointer_cast<BoolConstToken::CTYPE>(token._actual));
		break;
	case UNDEFINED:
		std::cout << "undefined";
		break;
	}
	return os << " |";
}
