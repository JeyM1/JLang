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
  protected:
	CurrentToken _currToken{};
	std::vector<Lexer::LineToken> _tokens{};
	std::vector<std::shared_ptr<IdentifierToken>> _identifiers;

  public:
	bool interpret( const std::vector<Lexer::LineToken>& tokens,
	                const std::vector<std::shared_ptr<IdentifierToken>>& identifiers );
};

#endif //_RPNINTERPRETER_H_
