//
// Created by Denis Afendikov on 25.04.2021.
//

#include "JFToken.h"


JFToken::JFToken()
	: Token(Token::Keyword, "JF") {}

std::string JFToken::toString() {
	return Token::toString() + "(" + std::to_string(this->jumpToIdx) + ")";
}
