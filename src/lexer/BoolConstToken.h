//
// Created by Denis Afendikov on 02.03.2021.
//

#ifndef _BOOLCONSTTOKEN_H_
#define _BOOLCONSTTOKEN_H_

#include "Token.h"
#include "../rpn_interpreter/VariableType.h"


class BoolConstToken : public Token
{
  public:
	typedef bool CTYPE;

  protected:
	std::shared_ptr<CTYPE> _actual;

  public:
	explicit BoolConstToken( const std::string& lexeme );
	explicit BoolConstToken( const CTYPE& actual );

	virtual std::shared_ptr<void> actual() const override {
		return _actual;
	}

	VariableType variableType() const override {
		return VariableType::BOOL;
	}
};

#endif //_BOOLCONSTTOKEN_H_
