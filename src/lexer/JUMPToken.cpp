//
// Created by Denis Afendikov on 25.04.2021.
//

#include "JUMPToken.h"

#include <utility>


JUMPToken::JUMPToken( std::shared_ptr<Token> jumpToken )
	: Token(Token::Keyword, "JUMP") {}