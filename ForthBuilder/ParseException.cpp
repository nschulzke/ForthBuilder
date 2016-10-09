#include "ParseException.h"

const std::string ParseException::MESSAGES[] = {
	"Unknown error",
	"Unknown name",
	"Unexpected end of file",
	"Unexpected token",
};

int ParseException::getWordNum() const
{
	return wordNum;
}

void ParseException::setWordNum(int wordNumIn)
{
	wordNum = wordNumIn;
}

Token ParseException::getToken() const
{
	return token;
}

std::string ParseException::getMessage() const
{
	return message;
}

int ParseException::getErrorCode() const
{
	return errorCode;
}

std::string ParseException::what() const
{
	return 	"Error while parsing: \"" + message + "\" on line \"" + std::to_string(wordNum) + "\" while parsing token \"" + token.toString() + "\"";
}