//
// Created by Denis Afendikov on 12.04.2021.
//

#ifndef _RPNINTERPRETER_H_
#define _RPNINTERPRETER_H_

#include <vector>
#include <memory>
#include <stack>
#include "../lexer/Token.h"
#include "../lexer/Lexer.h"


using CurrentToken = std::vector<Lexer::LineToken>::const_iterator;

class RPNInterpreter
{
  public:
	static const std::map<std::string, VariableType> variableTypes;
  protected:
	CurrentToken _currToken{};
	const std::vector<Lexer::LineToken>& _tokens;
	std::vector<std::shared_ptr<IdentifierToken>> _identifiers;
	std::stack<Lexer::LineToken> global_stack{};

	std::ostream& _interpreter_out;
	std::istream& _interpreter_in;

  public:
	RPNInterpreter( const std::vector<Lexer::LineToken>& tokens,
	                std::vector<std::shared_ptr<IdentifierToken>> identifiers,
	                std::ostream& interpreter_out = std::cout,
	                std::istream& interpreter_in = std::cin
	);

	bool interpret();
	bool postfixProcessing();
	void processAssign();
	void processBinary();
	void processInitialization();

	const std::vector<std::shared_ptr<IdentifierToken>>& getIdentifiers() const;
	void processUnary();
	void processPrint();
	void processJF();
	static std::shared_ptr<bool> parseBoolFromVar( std::shared_ptr<Token> token );
	void processJUMP();
	void processRead();
};

#endif //_RPNINTERPRETER_H_
