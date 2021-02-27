//
// Created by Denis Afendikov on 25.02.2021.
//

#include "Token.h"
Token::Token( Token::Type type ) : _type( type ) {}
Token::Token( Token::Type type, const std::string_view& lexeme ) : _type( type ), _lexeme( lexeme ) {}
