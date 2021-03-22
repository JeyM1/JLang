//
// Created by Denis Afendikov on 18.03.2021.
//

#ifndef _SYNTAXERROR_H_
#define _SYNTAXERROR_H_

#include <exception>
#include <string>
#include "../Parser.h"


class SyntaxError : public std::exception
{
	const std::string _message;
  public:
	explicit SyntaxError( const std::string& message );
	[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

#endif //_SYNTAXERROR_H_
