//
// Created by Denis Afendikov on 25.02.2021.
//

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string_view>

class Token
{
  public:
	enum Type
	{
		Identifier,
		IntConst,
		RealConst,
		BoolConst,
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
		Punct,
		Semicolon,
		Whitespace,
		EOL,
		FEOF,
		Unexpected
	};
  protected:
	Token::Type _type;
	std::string_view _lexeme;

  public:
	explicit Token( Type type );
	Token( Type type, const std::string_view& lexeme );

	Type type() const noexcept { return _type; }
	void setType( Type t ) noexcept { _type = t; }

	bool is( Type t ) const noexcept { return t == _type; }

	bool is_not( Type t ) const noexcept { return t != _type; }

	bool is_one_of( Type t1, Type t2 ) const noexcept { return is( t1 ) || is( t2 ); }

	template < typename... Ts >
	bool is_one_of( Type t1, Type t2, Ts... ts ) const noexcept {
		return is( t1 ) || is_one_of( t2, ts... );
	}

};

#endif //_TOKEN_H_
