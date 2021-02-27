//
// Created by Denis Afendikov on 27.02.2021.
//

#include <istream>
#include <iostream>
#include <sstream>
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

	{{ 0, Whitespace }, 0 }

};

const std::map<
	unsigned int,
	std::function<void( std::istream& in, std::stringstream& lexeme, char currChar, unsigned int currLine )>
> Lexer::finalStateProcessingFunctions = {
	{ 2, []( std::istream& in, std::stringstream& lexeme, char currChar, unsigned int currLine ) {
	  Token token = Token::getLanguageToken( lexeme.str());
	  if (token.is( Token::Unexpected )) {
		  // token is not Language-in, its identifier
		  // TODO: insert into tables
	  }

	  in.unget();
	}}
};

Lexer::LineToken::LineToken( const Token& token ) : token( token ) {}
Lexer::Lexer() {}
bool Lexer::lex( std::istream& inpStream ) noexcept {
	bool isSuccess = true;
	unsigned int currState = Lexer::initialState;
	unsigned int currLine = 1;
	std::stringstream lexeme;
	for (char ch; (ch = inpStream.get()) != EOF;) {
		ClassOfChar charClass = classOfChar( ch );
		std::cout << "class = " << charClass;
		std::cout << " | char = \"" << ch;
		std::cout << "\" | state = " << currState << std::endl;
		try {
			currState = stateTransitionFn.at( std::make_pair( currState, charClass ));
			std::cout << "Changed state to: " << currState << std::endl;
		}
		catch (std::exception& e) {
			std::cout << "Could not change state to ..., changing to other" << std::endl;
			currState = stateTransitionFn.at( std::make_pair( currState, Other ));
		}
		bool isStateFinal = finalStateProcessingFunctions.find( currState ) != finalStateProcessingFunctions.end();
		if (isStateFinal) {
			// call processing fn
			std::cout << "State is final, calling processing func.." << std::endl;
			finalStateProcessingFunctions.at( currState )( inpStream, lexeme, ch, currLine );
			currState = initialState;
		}
		else if (currState == initialState) {
			lexeme.str( std::string{} );
		}
		else {
			lexeme.put( ch );
			std::cout << "Changed lexeme to: " << lexeme.str() << std::endl;
		}
	}

	return isSuccess;
}
ClassOfChar Lexer::classOfChar( char ch ) {
	for (int charClassInt = 0; charClassInt < ClassOfChar::Other; charClassInt++) {
		auto cls = static_cast<ClassOfChar>(charClassInt);
		if (charClasses.at( cls ).find( ch ) != std::string::npos)
			return cls;
	}
	return Other;
}
