//
// Created by Denis Afendikov on 27.04.2021.
//

#ifndef _LEXERERROR_H_
#define _LEXERERROR_H_

#include <string>


class LexerError : public std::exception
{
	const std::string _message;
  public:
	explicit LexerError( const std::string& message );
	[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

#endif //_LEXERERROR_H_
