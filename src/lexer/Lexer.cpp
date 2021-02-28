//
// Created by Denis Afendikov on 27.02.2021.
//

#include <istream>
#include <iostream>
#include <sstream>
#include <utility>
#include <iomanip>
#include "Lexer.h"

using ClassOfChar = Lexer::ClassOfChar;

const std::map<ClassOfChar, std::string> Lexer::charClasses = {
	{ Letter, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" },
	{ Digit, "0123456789" },
	{ Whitespace, " \t" },
	{ Newline, "\r\n" },
};

const std::map<std::pair<unsigned int, ClassOfChar>, unsigned int> Lexer::stateTransitionFn = {
	// Identifier
	{{ 0, Letter }, 1 },
	{{ 1, Letter }, 1 },
	{{ 1, Digit }, 1 },
	{{ 1, Other }, 2 },

	// IntConst
	{{ 1, Other }, 2 },
	{{ 1, Other }, 2 },
	{{ 1, Other }, 2 },

	{{ 0, Whitespace }, 0 },

	// Unexpected
	{{ 0, Other }, 101 },


};

const std::map<
	unsigned int,
	std::function<void( std::istream& in, const std::string& lexeme, char currChar, unsigned int currLine, Lexer& instance )>
> Lexer::finalStateProcessingFunctions = {
	{ 2,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int currLine, Lexer& instance ) {
		Token token = Token::getLanguageToken(lexeme);
		if (token.is(Token::Unexpected)) {
			// token is not Language-in, its identifier
			// TODO: insert into tables
			auto it = std::find(instance.identifiers.begin(), instance.identifiers.end(), lexeme);

			if (it == instance.identifiers.end()) {
				// not found identifier in table
				instance.identifiers.push_back(lexeme);
			}

			token = Token{ Token::Type::Identifier, lexeme };
		}
		instance.tokens.emplace_back(currLine, token);
		in.unget();
	  }
	},

	{ 101,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int currLine, Lexer& instance ) {
		std::cout << "DEBUG: found unexpected token \"" << lexeme + currChar << "\" at line " << currLine << std::endl;
		instance.tokens.emplace_back(currLine, Token{Token::Type::Unexpected, lexeme + currChar});
	  }
	},

};

Lexer::LineToken::LineToken( unsigned int line, Token token ) : line(line), token(std::move(token)) {}
Lexer::Lexer() {}
bool Lexer::lex( std::istream& inpStream ) noexcept {
	bool isSuccess = true;
	unsigned int currState = Lexer::initialState;
	unsigned int currLine = 1;
	std::stringstream lexeme;
	for (char ch; (ch = inpStream.get()) != EOF;) {
		ClassOfChar charClass = classOfChar(ch);
		std::cout << "class = " << charClass;
		std::cout << " | char = \"" << ch;
		std::cout << "\" | state = " << currState << std::endl;
		try {
			currState = stateTransitionFn.at(std::make_pair(currState, charClass));
			std::cout << "Changed state to: " << currState << std::endl;
		}
		catch (std::exception& e) {
			try {
				currState = stateTransitionFn.at(std::make_pair(currState, Other));
				std::cout << "Changed state by Other to: " << currState << std::endl;
			}
			catch (...) {
				std::cerr << "No state to go from" << std::endl;
				isSuccess = false;
				// TODO: change to unexpected token
			}
		}
		bool isStateFinal = finalStateProcessingFunctions.count(currState) > 0;
		if (isStateFinal) {
			// call processing fn
			std::cout << "State " << currState << " is final, calling processing func" << std::endl;

			finalStateProcessingFunctions.at(currState)(inpStream, lexeme.str(), ch, currLine, *this);
			currState = initialState;
		}
		else if (currState == initialState) {
			lexeme.str(std::string{});
		}
		else {
			lexeme.put(ch);
			std::cout << "Changed lexeme to: " << lexeme.str() << std::endl;
		}
	}

	return isSuccess;
}
ClassOfChar Lexer::classOfChar( char ch ) {
	for (int charClassInt = 0; charClassInt < ClassOfChar::Other; charClassInt++) {
		auto cls = static_cast<ClassOfChar>(charClassInt);
		if (charClasses.at(cls).find(ch) != std::string::npos)
			return cls;
	}
	return Other;
}
void Lexer::printTokenTable() {
	for (const auto& lineToken : this->tokens) {
		std::cout << std::setw(3) << lineToken.line << " | " << lineToken.token << std::endl;
	}
}
