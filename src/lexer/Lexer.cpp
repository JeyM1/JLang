//
// Created by Denis Afendikov on 27.02.2021.
//

#include <istream>
#include <iostream>
#include <sstream>
#include <utility>
#include <iomanip>
#include <memory>
#include "Lexer.h"
#include "BoolConstToken.h"

using ClassOfChar = Lexer::ClassOfChar;

const std::map<ClassOfChar, std::string> Lexer::charClasses = {
	{ Letter, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" },
	{ Digit, "0123456789" },
	{ Whitespace, " \t" },
	{ Newline, "\r\n" },
	{ Dot, "." },
};

const std::map<std::pair<unsigned int, ClassOfChar>, unsigned int> Lexer::stateTransitionFn = {
	// Identifiers, Keywords or BoolConsts
	{{ 0, Letter }, 1 },
	{{ 1, Letter }, 1 },
	{{ 1, Digit }, 1 },
	{{ 1, Other }, 2 },

	// UnsignedReal
	{{ 0, Digit }, 3 },
	{{ 3, Digit }, 3 },
	// if UnsignedInt
	{{ 3, Other }, 8 },
	{{ 3, Dot }, 4 },
	{{ 4, Digit }, 4 },
	{{ 4, Other }, 5 },
	{{ 0, Dot }, 6 },
	{{ 6, Digit }, 4 },
	//


	// Whitespace
	{{ 0, Whitespace }, 0 },

	// NewLine
	{{ 0, Newline }, 9 },

	// Unexpected
	{{ 0, Other }, 101 },

};

const std::map<
	unsigned int,
	std::function<void( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance )>
> Lexer::finalStateProcessingFunctions = {
	{ 2,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    std::shared_ptr<Token> token = Token::getLanguageToken(lexeme);
	    if (token->is(Token::Unexpected)) {
		    // token is not Language-in, its identifier
		    auto it = std::find(instance.identifiers.begin(), instance.identifiers.end(), lexeme);
		    if (it == instance.identifiers.end()) {
			    // not found identifier in table
			    instance.identifiers.push_back(lexeme);
		    }

		    token = std::make_shared<Token>(Token::Type::Identifier, lexeme);
	    }
	    instance.tokens.emplace_back(currLine, token);
	    in.unget();
	  }
	},

	// UnsignedReal
	{ 5,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    if (std::string{ currChar } == charClasses.at(ClassOfChar::Dot)) {
		    // TODO: set next token to Unexpected
		    std::cout << "Invalid suffix on real constant!" << std::endl;
	    }
	    std::shared_ptr<Token> token = std::make_shared<Token>(Token::Type::UnsignedReal, lexeme);
	    instance.tokens.emplace_back(currLine, token);
	    in.unget();
	  }
	},

	// UnsignedInt
	{ 8,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    std::shared_ptr<Token> token = std::make_shared<Token>(Token::Type::UnsignedInt, lexeme);
	    instance.tokens.emplace_back(currLine, token);
	    in.unget();
	  }
	},

	// Newline
	{ 9,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    currLine++;
	  }
	},


	// Error state
	{ 101,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int currLine, Lexer& instance ) {
	    std::cout << "DEBUG: found unexpected token \"" << lexeme + currChar << "\" at line " << currLine << std::endl;
	    instance.tokens.emplace_back(currLine, std::make_shared<Token>(Token::Type::Unexpected, lexeme + currChar));
	  }
	},

};

Lexer::LineToken::LineToken( unsigned int line, std::shared_ptr<Token> token ) : line(line), token(std::move(token)) {}
Lexer::Lexer() {}

bool Lexer::lex( std::istream& inpStream ) noexcept {
	unsigned int currLine = 1;
	std::stringstream lexeme;
	for (char ch; (ch = inpStream.get()) != EOF;) {
		ClassOfChar charClass = classOfChar(ch);
		std::cout << "class = " << charClass;
		std::cout << " | char = \"" << ch;
		std::cout << "\" | state = " << this->currState << std::endl;
		try {
			this->currState = stateTransitionFn.at(std::make_pair(this->currState, charClass));
			std::cout << "Changed state to: " << this->currState << std::endl;
		}
		catch (std::exception& e) {
			try {
				this->currState = stateTransitionFn.at(std::make_pair(this->currState, Other));
				std::cout << "Changed state by Other to: " << this->currState << std::endl;
			}
			catch (...) {
				std::cerr << "No state to go from " << this->currState << std::endl;
				this->isLastLexSuccess = false;
				// TODO: change to unexpected token
			}
		}
		bool isStateFinal = finalStateProcessingFunctions.count(this->currState) > 0;
		if (isStateFinal) {
			// call processing fn
			std::cout << "State " << this->currState << " is final, calling processing func" << std::endl;

			finalStateProcessingFunctions.at(this->currState)(inpStream, lexeme.str(), ch, currLine, *this);
			this->currState = initialState;
			lexeme.str(std::string{});
		}
		else if (this->currState == initialState) {
			lexeme.str(std::string{});
		}
		else {
			lexeme.put(ch);
			std::cout << "Changed lexeme to: " << lexeme.str() << std::endl;
		}
	}

	return this->isLastLexSuccess;
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
		std::cout << std::setw(3) << lineToken.line << " | " << *lineToken.token;
		if (lineToken.token->is(Token::Type::BoolConst)) {
			std::cout << " actual: " << std::dynamic_pointer_cast<BoolConstToken>(lineToken.token)->actual();
		}
		std::cout << std::endl;
	}
}
