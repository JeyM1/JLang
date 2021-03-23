//
// Created by Denis Afendikov on 25.02.2021.
//

#include <map>
#include <iostream>
#include <utility>
#include <memory>
#include <vector>
#include <algorithm>
#include "Token.h"
#include "BoolConstToken.h"
#include "../logger.h"
#include "../utils.h"


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
	{ "true", Type::BoolConst },
	{ "false", Type::BoolConst },
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
	{ "!", Type::Not },
	{ "&&", Type::And },
	{ "||", Type::Or },
	{ "(", Type::LeftParen },
	{ ")", Type::RightParen },
	{ "{", Type::LeftCurly },
	{ "}", Type::RightCurly },
//	{ ".", Type::Punct },
	{ ",", Type::Comma },
//	{ ":", Type::Punct },
	{ ";", Type::Semicolon },
//	{ " ", Type::Whitespace },
//	{ "\t", Type::Whitespace },
//	{ "\n", Type::EOL },
//	{ "\r\n", Type::EOL },
//	{ "\0", Type::FEOF },
};

Token::Token( Token::Type type, std::string lexeme ) : _type(type), _lexeme(std::move(lexeme)) {}

std::shared_ptr<Token> Token::getLanguageToken( const std::string& lexeme ) {
	try {
		Type t = languageTokens.at(lexeme);
		if (t == Type::BoolConst) {
			return std::make_shared<BoolConstToken>(lexeme);
		}
		return std::make_shared<Token>(t, lexeme);
	}
	catch (...) {
		log("Lexer: ") << "Unexpected language token \"" << lexeme << "\"" << std::endl;
	}
	return std::make_shared<Token>(Unexpected, lexeme);
}

std::ostream& operator<<( std::ostream& os, const Token& token ) {
	os << "type: " << token._type << " lexeme: " << token._lexeme;
	return os;
}

Token::~Token() {

}

std::string Token::getClosestLanguageToken( const std::string& lexeme ) {
	std::vector<std::string> keys;

	std::transform(
		languageTokens.begin(),
		languageTokens.end(),
		std::back_inserter(keys),
		[]( const std::map<const std::string, Token::Type>::value_type& pair ) { return pair.first; }
	);

	auto closest = keys.begin();
	int minEditDist = 100000;
	for (auto it = closest; it != keys.end(); ++it) {
		int dist = editDist(*it, lexeme, it->size(), lexeme.size());
		if (dist < minEditDist) {
			closest = it;
			minEditDist = dist;
		}
	}

	return *closest;
}
