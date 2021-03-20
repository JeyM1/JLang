//
// Created by Denis Afendikov on 18.03.2021.
//

#ifndef _SYNTAXERROR_H_
#define _SYNTAXERROR_H_

#include <exception>
#include <string>


class SyntaxError : public std::exception
{
	const unsigned int _line;
	const std::string _message;
  public:
	SyntaxError( unsigned int line, const std::string&  message );
	[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

#endif //_SYNTAXERROR_H_
