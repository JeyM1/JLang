//
// Created by Denis Afendikov on 12.04.2021.
//

#ifndef _IDENTIFIERTOKEN_H_
#define _IDENTIFIERTOKEN_H_

#include "Token.h"


class IdentifierToken : public Token
{
  public:
	enum Type
	{
		INT,
		REAL,
		BOOL,
		UNDEFINED
	};

  protected:
	IdentifierToken::Type _identifierType;
	std::shared_ptr<void> _value;
	unsigned int _id;

  public:
	IdentifierToken( const std::string& lexeme, unsigned int id );
	void setIdentifierType( IdentifierToken::Type type );
	void setValue( std::shared_ptr<void> value );

	Type identifierType() const {
		return _identifierType;
	}

	const std::shared_ptr<void>& value() const {
		return _value;
	}

	unsigned int id() const {
		return _id;
	}

};

#endif //_IDENTIFIERTOKEN_H_
