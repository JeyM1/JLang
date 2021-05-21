//
// Created by Denis Afendikov on 25.04.2021.
//

#ifndef _JFTOKEN_H_
#define _JFTOKEN_H_

#include "Token.h"


class JFToken : public Token
{
  public:
	JFToken();
	unsigned int jumpToIdx;
	std::string toString() override;
};

#endif //_JFTOKEN_H_
