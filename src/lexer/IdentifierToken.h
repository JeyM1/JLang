//
// Created by Denis Afendikov on 12.04.2021.
//

#ifndef _IDENTIFIERTOKEN_H_
#define _IDENTIFIERTOKEN_H_

#include "Token.h"
#include "../rpn_interpreter/VariableType.h"


class IdentifierToken : public Token
{
  protected:
	VariableType _variableType;
	std::shared_ptr<void> _actual;
	unsigned int _id;

  public:
	IdentifierToken( const std::string& lexeme, unsigned int id );
	void setVariableType( VariableType type );
	void setActual( std::shared_ptr<void> value, VariableType from );

	VariableType variableType() const override {
		return _variableType;
	}

	std::shared_ptr<void> actual() const override;

	unsigned int id() const {
		return _id;
	}

	friend std::ostream& operator<<( std::ostream& os, const IdentifierToken& token );
};

#endif //_IDENTIFIERTOKEN_H_
