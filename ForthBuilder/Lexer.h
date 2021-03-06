#pragma once

#include "FileIO.h"

class Lexer
{
private:
	FileIO* fileManager;
	std::vector<Token> tokens;

	/// Takes a file and lexes it, turning it into a vector of tokens
	void lex(const std::string &fileNameIn);
public:
	Lexer(const std::string &fileNameIn, FileIO* fileManagerIn);

	static void split(const std::string &stringIn, char delimIn, std::vector<std::string> &elemsIn);
	static void split(char delimIn, std::vector<std::string> &elemsIn);
	static std::vector<std::string> split(const std::string &stringIn);

	/// Return the begin iterator for the tokens vector
	std::vector<Token>::const_iterator begin() const { return tokens.begin(); };
	/// Return the end iterator for the tokens vector
	std::vector<Token>::const_iterator end() const { return tokens.end(); };
};

