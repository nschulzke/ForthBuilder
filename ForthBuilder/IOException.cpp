#include "IOException.h"

const std::string IOException::MESSAGES[] = {
	"unknown error",
	"reading",
	"writing"
};

std::string IOException::getFileName() const { return fileName; }

std::string IOException::getMessage() const { return message; }

IOException::Code IOException::getErrorCode() const { return errorCode; }

std::string IOException::what() const
{
	return 	"Error: \"" + message + "\" File: \"" + fileName + "\"";
}