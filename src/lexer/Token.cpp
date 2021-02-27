//
// Created by Denis Afendikov on 25.02.2021.
//

#include <map>
#include <iostream>
#include <utility>
#include "Token.h"


using Type = Token::Type;

const std::map<const std::string, Type> Token::languageTokens = {
	{ "program", Type::Keyword },
	{ "int", Type::Keyword },
	{ "real", Type::Keyword },
	{ "bool", Type::Keyword },
	{ "read", Type::Keyword },
	{ "print", Type::Keyword },
	{ "for", Type::Keyword },
	{ "by", Type::Keyword },
	{ "while", Type::Keyword },
	{ "do", Type::Keyword },
	{ "if", Type::Keyword },
	{ "then", Type::Keyword },
	{ "else", Type::Keyword },
	{ "=", Type::Assign },
	{ "+", Type::Add },
	{ "-", Type::Sub },
	{ "*", Type::Multiply },
	{ "/", Type::Division },
	{ "//", Type::IntDivision },
	{ "**", Type::Power },
	{ "<", Type::LessThan },
	{ "<=", Type::LessOrEqualTo },
	{ "==", Type::EqualTo },
	{ ">=", Type::GreaterOrEqualTo },
	{ ">", Type::GreaterThan },
	{ "!=", Type::NotEqual },
	{ "(", Type::LeftParen },
	{ ")", Type::RightParen },
	{ "{", Type::LeftCurly },
	{ "}", Type::RightCurly },
	{ ".", Type::Punct },
	{ ",", Type::Punct },
	{ ":", Type::Punct },
	{ ";", Type::Semicolon },
	{ " ", Type::Whitespace },
	{ "\t", Type::Whitespace },
	{ "\n", Type::EOL },
	{ "\r\n", Type::EOL },
	{ "\0", Type::FEOF },
};

Token::Token( Token::Type type, std::string lexeme ) : _type( type ), _lexeme(std::move( lexeme )) {}
Token Token::getLanguageToken(const std::string& lexeme) {
	try{
		Type t = languageTokens.at(lexeme);

		return Token{t, lexeme};
	} catch (...) {
		// TODO: remove message
		std::cout << "Unexpected language token \"" << lexeme << "\"" << std::endl;
	}
	return Token( Unexpected, lexeme);
}
