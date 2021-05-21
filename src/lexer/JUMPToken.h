//
// Created by Denis Afendikov on 25.04.2021.
//

#ifndef _JUMPTOKEN_H_
#define _JUMPTOKEN_H_

#include "Token.h"


class JUMPToken : public Token
{
  public:
	JUMPToken();
	unsigned int jumpToIdx;
	std::string toString() override;
};

#endif //_JUMPTOKEN_H_
