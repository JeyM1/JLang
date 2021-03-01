//
// Created by Denis Afendikov on 25.02.2021.
//

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string_view>
#include <ostream>

class Token
{
  public:
	enum Type
	{
		Identifier,
		IntConst,
		RealConst,
		BoolConst,
		UnsignedInt,
		UnsignedReal,
		Keyword,
		Assign,
		Add,
		Sub,
		Multiply,
		Division,
		IntDivision,
		Power,
		LessThan,
		LessOrEqualTo,
		EqualTo,
		GreaterOrEqualTo,
		GreaterThan,
		NotEqual,
		LeftParen,
		RightParen,
		LeftCurly,
		RightCurly,
		Semicolon,
		EOL,
		FEOF,
		Unexpected
	};

	static const std::map<const std::string, Token::Type> languageTokens;

  protected:
	Token::Type _type;
	std::string _lexeme;

  public:
	Token( Type type, std::string  lexeme );

	Type type() const noexcept { return _type; }
	void setType( Type t ) noexcept { _type = t; }

	bool is( Type t ) const noexcept { return t == _type; }

	bool is_not( Type t ) const noexcept { return t != _type; }

	bool is_one_of( Type t1, Type t2 ) const noexcept { return is( t1 ) || is( t2 ); }

	template < typename... Ts >
	bool is_one_of( Type t1, Type t2, Ts... ts ) const noexcept {
		return is( t1 ) || is_one_of( t2, ts... );
	}

	static Token getLanguageToken(const std::string&);
	friend std::ostream& operator<<( std::ostream& os, const Token& token );

};

#endif //_TOKEN_H_
