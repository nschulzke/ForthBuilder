#pragma once

#include <string>
#include "Token.h"

class IOException
{
public:
	// Error code constants
	enum Code
	{
		OTHER_ERROR = 0,
		READ_ERROR,
		WRITE_ERROR
	};
private:
	std::string message;
	std::string fileName;
	Code errorCode;
public:
	static const std::string MESSAGES[];
	IOException(Code errorCodeIn, std::string fileNameIn) :
		message(MESSAGES[errorCodeIn]),
		errorCode(errorCodeIn),
		fileName(fileNameIn)
	{};
	/// Retrieve the name of the file that caused the exception
	std::string getFileName() const;
	/// Retrieve the human-readable message of the exception
	std::string getMessage() const;
	/// Retrieve the error code of the exception
	Code getErrorCode() const;
	/// Get a complete, human-readable description of the exception
	std::string what() const;
};