#pragma once

#include <vector>
#include "Word.h"
#include "Primitive.h"
#include "Lexer.h"

class Parser
{
private:
	std::vector<Word> words;
	std::vector<Primitive> primitives;

	// Returns a vector of words built out of the input vector
	void parse(const Lexer &lexerIn);
	void iterate(const Lexer &lexerIn, std::vector<Token>::const_iterator& it);
	void checkMatch(const Token &tokenIn, const Token::Type &typeIn, const std::string nameIn = "");
	void ignoreComment(const Lexer &lexerIn, std::vector<Token>::const_iterator& it);
	void handleColonDef(const Lexer &lexerIn, std::vector<Token>::const_iterator &it);
	void handleVariable(const Lexer &lexerIn, std::vector<Token>::const_iterator &it);
	void handleConstant(const Lexer &lexerIn, std::vector<Token>::const_iterator &it);
	void handlePrimitive(const Lexer &lexerIn, std::vector<Token>::const_iterator &it);
public:
	Parser(const Lexer &lexerIn);
	const std::vector<Word> &wordList() const { return words; };
	const std::vector<Primitive> &primitiveList() const { return primitives; };
};

