//
// Created by Denis Afendikov on 12.04.2021.
//

#ifndef _RUNTIMEERROR_H_
#define _RUNTIMEERROR_H_

#include <exception>
#include <string>


class RunTimeError : public std::exception
{
	const std::string _message;
  public:
	explicit RunTimeError( const std::string& message );
	[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

#endif //_RUNTIMEERROR_H_
