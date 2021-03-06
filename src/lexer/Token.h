//
// Created by Denis Afendikov on 25.02.2021.
//

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string_view>
#include <iostream>
#include <map>
#include <memory>


class Token
{
  public:
	enum Type
	{
		// 0
		Identifier,
		// 1
		Keyword,
		// 2
		IntConst,
		// 3
		RealConst,
		// 4
		BoolConst,
		// 5
		Assign,
		// 6
		Add,
		// 7
		Sub,
		// 8
		Multiply,
		// 9
		Division,
		// 10
		IntDivision,
		// 11
		Power,
		// 12
		LessThan,
		// 13
		LessOrEqualTo,
		// 14
		EqualTo,
		// 15
		GreaterOrEqualTo,
		// 16
		GreaterThan,
		// 17
		NotEqual,
		// 18
		And,
		// 19
		Or,
		// 20
		LeftParen,
		// 21
		RightParen,
		// 22
		LeftCurly,
		// 23
		RightCurly,
		// 24
		Semicolon,
		// 25
		EOL,
		// 26
		FEOF,
		// 27
		Unexpected
	};

	static const std::map<const std::string, Token::Type> languageTokens;

  protected:
	Token::Type _type;
	std::string _lexeme;

  public:
	Token( Type type, std::string lexeme );
	virtual ~Token();

	Type type() const noexcept { return _type; }

	void setType( Type t ) noexcept { _type = t; }

	bool is( Type t ) const noexcept { return t == _type; }

	bool is_not( Type t ) const noexcept { return t != _type; }

	bool is_one_of( Type t1, Type t2 ) const noexcept { return is(t1) || is(t2); }

	template < typename... Ts >
	bool is_one_of( Type t1, Type t2, Ts... ts ) const noexcept {
		return is(t1) || is_one_of(t2, ts...);
	}

	static std::shared_ptr<Token> getLanguageToken( const std::string& );
	static std::string getClosestLanguageToken( const std::string& );

	friend std::ostream& operator<<( std::ostream& os, const Token& token );

};

#endif //_TOKEN_H_
