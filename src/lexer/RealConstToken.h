//
// Created by Denis Afendikov on 02.03.2021.
//

#ifndef _REALCONSTTOKEN_H_
#define _REALCONSTTOKEN_H_

#include "Token.h"
#include "../rpn_interpreter/VariableType.h"


class RealConstToken : public Token
{
  public:
	typedef long double CTYPE;

  protected:
	std::shared_ptr<CTYPE> _actual;
  public:
	explicit RealConstToken( const std::string& lexeme );
	explicit RealConstToken( const CTYPE& actual );

	virtual std::shared_ptr<void> actual() const override {
		return _actual;
	}

	virtual VariableType variableType() const override {
		return VariableType::REAL;
	}
};

#endif //_REALCONSTTOKEN_H_
