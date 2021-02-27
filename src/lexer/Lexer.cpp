//
// Created by Denis Afendikov on 27.02.2021.
//

#include <istream>
#include <iostream>
#include "Lexer.h"

using Type = Token::Type;

const std::map<std::string, Type> Lexer::languageTokens = {
	{"program", Type::Keyword},
	{"int", Type::Keyword},
	{"real", Type::Keyword},
	{"bool", Type::Keyword},
	{"read", Type::Keyword},
	{"print", Type::Keyword},
	{"for", Type::Keyword},
	{"by", Type::Keyword},
	{"while", Type::Keyword},
	{"do", Type::Keyword},
	{"if", Type::Keyword},
	{"then", Type::Keyword},
	{"else", Type::Keyword},
	{"=", Type::Assign},
	{"+", Type::Add},
	{"-", Type::Sub},
	{"*", Type::Multiply},
	{"/", Type::Division},
	{"//", Type::IntDivision},
	{"**", Type::Power},
	{"<", Type::LessThan},
	{"<=", Type::LessOrEqualTo},
	{"==", Type::EqualTo},
	{">=", Type::GreaterOrEqualTo},
	{">", Type::GreaterThan},
	{"!=", Type::NotEqual},
	{"(", Type::LeftParen},
	{")", Type::RightParen},
	{"{", Type::LeftCurly},
	{"}", Type::RightCurly},
	{".", Type::Punct},
	{",", Type::Punct},
	{":", Type::Punct},
	{";", Type::Semicolon},
	{" ", Type::Whitespace},
	{"\t", Type::Whitespace},
	{"\n", Type::EOL},
	{"\r\n", Type::EOL},
	{"\0", Type::FEOF},
};


Lexer::LineToken::LineToken( const Token& token ) : token( token ) {}
Lexer::Lexer() {}
void Lexer::lex( std::istream& inpStream ) noexcept {
	for (char ch; (ch = inpStream.get()) != EOF; ) {
		std::cout << ch;
	}
}