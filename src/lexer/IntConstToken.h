//
// Created by Denis Afendikov on 02.03.2021.
//

#ifndef _INTCONSTTOKEN_H_
#define _INTCONSTTOKEN_H_

#include "Token.h"
#include "../rpn_interpreter/VariableType.h"


class IntConstToken : public Token
{
  public:
	typedef int CTYPE;

  protected:
	std::shared_ptr<CTYPE> _actual;

  public:
	explicit IntConstToken( const std::string& lexeme );
	explicit IntConstToken( const CTYPE& actual );

	virtual std::shared_ptr<void> actual() const override {
		return _actual;
	}

	virtual VariableType variableType() const override {
		return VariableType::INT;
	}
};

#endif //_INTCONSTTOKEN_H_
