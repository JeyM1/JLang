//
// Created by Denis Afendikov on 25.04.2021.
//

#ifndef _JUMPTOKEN_H_
#define _JUMPTOKEN_H_

#include "Token.h"
#include "../rpn_interpreter/RPNInterpreter.h"


class JUMPToken : public Token
{
  public:
	JUMPToken();
	CurrentToken jumpToken;
};

#endif //_JUMPTOKEN_H_
