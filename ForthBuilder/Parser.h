#pragma once

#include <vector>
#include "Word.h"
#include "Lexer.h"

class Parser
{
private:
	std::vector<Word> words;

	// Returns a vector of words built out of the input vector
	void parse(const Lexer* lexerIn);
	void ignoreComment(const Lexer* lexerIn, std::vector<Token>::const_iterator& it);
public:
	Parser(const Lexer* lexerIn);

	/// Return the begin iterator for the words vector
	std::vector<Word>::const_iterator begin() const { return words.begin(); };
	/// Return the end iterator for the words vector
	std::vector<Word>::const_iterator end() const { return words.end(); };
};

