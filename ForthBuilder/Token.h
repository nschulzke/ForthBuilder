#pragma once

#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <sstream>

#include "boost\tokenizer.hpp"
#include "FileIO.h"

class Token
{
public:
	enum Type {
		INVALID_TOKEN = 0,
		WORD = 1,
		NUMBER = 2,
		STRING = 4,
		PRIMITIVE = 8,
	};
private:
	// The string value of the token
	std::string tokenString;
	// The type of token
	Token::Type type;
public:
	// Takes a string and identifies what type of token it is. Static function.
	static Token::Type idToken(const std::string& tokenString);
	// Creates a tokenString with an empty string and INVALID_TOKEN as the type.
	Token();
	// Creates a tokenString by pushing the supplied string through idToken().
	Token(const std::string& tokenIn);
	// Gets the type of the tokenString.
	Token::Type getType() const;
	// Gets the string associated with the tokenString.
	std::string getString() const;
	// Gets a displayable representation of the entire token
	std::string toString() const;

	// Defines the insertion operator for the Token class
	friend std::ostream& operator<<(std::ostream& outstream, const Token& token);
	friend bool operator==(const Token& lhs, const Token& rhs);
	// Overloads the insertion operator for Token::Type objects
	friend std::ostream& operator<<(std::ostream& outstream, const Token::Type&  token);
	// toString function for Token::Type enum
	friend std::string to_string(const Token::Type&  type);
	// Overloads the OR operator so they can be combined (A | B)
	friend Token::Type operator|(const Token::Type&  a, const Token::Type&  b);
	// Overloads the AND operator so we can compare ((A | B) & (B | C) = B)
	friend Token::Type operator&(const Token::Type&  a, const Token::Type&  b);
};