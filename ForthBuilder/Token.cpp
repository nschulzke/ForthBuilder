#include "Token.h"

typedef boost::escaped_list_separator<char> list_separator;
typedef boost::tokenizer<list_separator> tokenizer;

Token::Type Token::idToken(const std::string& tokenString)
{
	std::regex number("(^[-]?[0-9]+$)");
	std::regex directive("(^#.*$)");
	if (std::regex_match(tokenString, number))
		return NUMBER;
	if (std::regex_match(tokenString, directive))
		return DIRECTIVE;
	else
		return WORD;
}

Token::Token(const std::string& tokenIn)
{
	tokenString = tokenIn;
	type = idToken(tokenIn);
}

Token::Token()
{
	tokenString = "";
	type = INVALID_TOKEN;
}

Token::Type Token::getType() const
{
	return type;
}

std::string Token::getString() const
{
	return tokenString;
}

std::string Token::toString() const
{
	// Make sure that the token is displayed all on one line
	std::string displayToken = tokenString;
	if (displayToken == "\n")
	{
		displayToken = "\\n";
	}
	return to_string(type) + "(" + tokenString + ")";
}

std::ostream& operator<<(std::ostream& outstream, const Token& token)
{
	outstream << token.toString();
	return outstream;
}

bool operator==(const Token & lhs, const Token & rhs)
{
	if (lhs.getType() == rhs.getType() && lhs.getString() == rhs.getString())
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& outstream, const Token::Type& type)
{
	return outstream << to_string(type);
}

std::string to_string(const Token::Type& type)
{
	switch (type)
	{
	case Token::Type::WORD:			return "WORD"; break;
	case Token::Type::NUMBER:		return "NUMBER"; break;
	case Token::Type::PRIMITIVE:	return "PRIMITIVE"; break;
	default:						return "INVALID_TOKEN";
	}
}

Token::Type operator|(const Token::Type& a, const Token::Type& b)
{
	return static_cast<Token::Type>(static_cast<int>(a) | static_cast<int>(b));
}

Token::Type operator&(const Token::Type& a, const Token::Type& b)
{
	return static_cast<Token::Type>(static_cast<int>(a) & static_cast<int>(b));
}