#pragma once

#include <string>
#include "Token.h"

class ParseException
{
public:
	// Error code constants
	enum Code
	{
		OTHER_ERROR = 0,
		UNKNOWN_NAME,
		UNEXPECTED_EOF,
		EXPECTED_WORD,
		EXPECTED_DEF_WORD
	};
private:
	std::string message;
	int wordNum;
	Token token;
	Code errorCode;
public:
	static const std::string MESSAGES[];
	ParseException(Code errorCodeIn) :
		message(MESSAGES[errorCodeIn]),
		errorCode(errorCodeIn),
		wordNum(-1)
	{};
	ParseException(Code errorCodeIn, const Token &tokenIn, int wordNumIn = -1) :
		message(MESSAGES[errorCodeIn]),
		token(tokenIn),
		wordNum(wordNumIn),
		errorCode(errorCodeIn)
	{};
	int getWordNum() const;
	void setWordNum(int wordNumIn);
	Token getToken() const;
	std::string getMessage() const;
	std::string what() const;
	int getErrorCode() const;
};
