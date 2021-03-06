//
// Created by Denis Afendikov on 02.03.2021.
//

#ifndef _INTCONSTTOKEN_H_
#define _INTCONSTTOKEN_H_

#include "Token.h"


class IntConstToken : public Token
{
  protected:
	int _actual;

  public:
	explicit IntConstToken( const std::string& lexeme );

	int actual() const {
		return _actual;
	}

};

#endif //_INTCONSTTOKEN_H_
