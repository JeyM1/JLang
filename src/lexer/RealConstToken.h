//
// Created by Denis Afendikov on 02.03.2021.
//

#ifndef _REALCONSTTOKEN_H_
#define _REALCONSTTOKEN_H_

#include "Token.h"


class RealConstToken : public Token
{
  protected:
	long double _actual;
  public:
	explicit RealConstToken( const std::string& lexeme );

	long double actual() const {
		return _actual;
	}
};

#endif //_REALCONSTTOKEN_H_
