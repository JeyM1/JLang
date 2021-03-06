//
// Created by Denis Afendikov on 02.03.2021.
//

#ifndef _BOOLCONSTTOKEN_H_
#define _BOOLCONSTTOKEN_H_

#include "Token.h"


class BoolConstToken : public Token
{
  protected:
	bool _actual;

  public:
	explicit BoolConstToken( const std::string& lexeme );

	bool actual() const {
		return _actual;
	}
};

#endif //_BOOLCONSTTOKEN_H_
