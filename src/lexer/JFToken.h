//
// Created by Denis Afendikov on 25.04.2021.
//

#ifndef _JFTOKEN_H_
#define _JFTOKEN_H_

#include "Token.h"
#include "../rpn_interpreter/RPNInterpreter.h"


class JFToken : public Token
{
  public:
	JFToken();
	CurrentToken jumpToken;
};

#endif //_JFTOKEN_H_
