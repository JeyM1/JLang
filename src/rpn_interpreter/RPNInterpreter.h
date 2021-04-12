//
// Created by Denis Afendikov on 12.04.2021.
//

#ifndef _RPNINTERPRETER_H_
#define _RPNINTERPRETER_H_

#include <vector>
#include <memory>
#include "../lexer/Token.h"
#include "../lexer/Lexer.h"


using CurrentToken = std::vector<Lexer::LineToken>::const_iterator;

class RPNInterpreter
{
	CurrentToken _currToken{};

  public:
	bool interpret(std::vector<Lexer::LineToken> tokens);
};

#endif //_RPNINTERPRETER_H_
