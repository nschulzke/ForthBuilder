#include "Parser.h"
#include "boost/algorithm/string.hpp"

Parser::Parser(const Lexer & lexerIn)
{
	parse(lexerIn);
}

void Parser::iterate(const Lexer &lexerIn, std::vector<Token>::const_iterator& it)
{
	if (it + 1 < lexerIn.end())
		it++;
	else
		throw ParseException(ParseException::UNEXPECTED_EOF, *it);
}

void Parser::checkMatch(const Token &tokenIn, const Token::Type &typeIn, const std::string nameIn)
{
	if (nameIn != "" && tokenIn.getString() != nameIn)
		throw ParseException(ParseException::UNEXPECTED_TOKEN, tokenIn);
	if (tokenIn.getType() != typeIn)
		throw ParseException(ParseException::UNEXPECTED_TOKEN, tokenIn);
}

void Parser::ignoreComment(const Lexer &lexerIn, std::vector<Token>::const_iterator& it)
{
	iterate(lexerIn, it);
	bool foundEnd = false;
	for (it; it < lexerIn.end(); it++)
	{
		if (it->getType() == Token::WORD && it->getString() == ")")
		{
			foundEnd = true;
			break;
		}
	}
	if (!foundEnd && it == lexerIn.end())
		throw ParseException(ParseException::UNEXPECTED_EOF, *it);
}

void Parser::handleColonDef(const Lexer &lexerIn, std::vector<Token>::const_iterator &it)
{
	std::vector<Token> tokens;

	iterate(lexerIn, it);
	std::string name = it->getString();
	iterate(lexerIn, it);
	for (it; it < lexerIn.end(); it++)
	{
		if (it->getString() == "(")
			ignoreComment(lexerIn, it);
		else if (it->getType() == Token::WORD && it->getString() == ";")
		{
			words.push_back(Word(Word::FUNCTION, name, tokens));
			tokens.clear();
			break;
		}
		else
			tokens.push_back(*it);
	}
	if (!tokens.empty() && it == lexerIn.end())
		throw ParseException(ParseException::UNEXPECTED_EOF, *it);
}

void Parser::handleVariable(const Lexer &lexerIn, std::vector<Token>::const_iterator &it)
{
	iterate(lexerIn, it);
	checkMatch(*it, Token::WORD);
	words.push_back(Word(Word::VARIABLE, it->getString()));
}

void Parser::handleConstant(const Lexer &lexerIn, std::vector<Token>::const_iterator &it)
{
	Token temp = *it;
	iterate(lexerIn, it);
	checkMatch(*it, Token::WORD, "CONSTANT");
	iterate(lexerIn, it);
	checkMatch(*it, Token::WORD);
	words.push_back(Word(Word::CONSTANT, it->getString(), temp));
}

void Parser::handlePrimitive(const Lexer & lexerIn, std::vector<Token>::const_iterator & it)
{
	std::string nameOut;
	std::string labelOut;
	int flagsOut = 0;

	iterate(lexerIn, it);
	checkMatch(*it, Token::WORD);
	nameOut = it->getString();

	iterate(lexerIn, it);
	checkMatch(*it, Token::WORD);
	labelOut = it->getString();

	iterate(lexerIn, it);
	if (it->getType() == Token::NUMBER)
	{
		flagsOut = stoi(it->getString());
		iterate(lexerIn, it);
	}
	checkMatch(*it, Token::WORD, "{");

	iterate(lexerIn, it);
	checkMatch(*it, Token::WORD, "}");

	primitives.push_back(Primitive(nameOut, labelOut, flagsOut));
}

void Parser::parse(const Lexer &lexerIn)
{
	for (std::vector<Token>::const_iterator it = lexerIn.begin(); it < lexerIn.end(); it++)
	{
		if (it->getType() == Token::WORD)
		{
			if (it->getString() == ":")
				handleColonDef(lexerIn, it);
			else if (it->getString() == "(")
				ignoreComment(lexerIn, it);
			else if (it->getString() == "VARIABLE")
				handleVariable(lexerIn, it);
			else
				throw ParseException(ParseException::UNEXPECTED_TOKEN, *it);
		}
		else if (it->getType() == Token::NUMBER)
			handleConstant(lexerIn, it);
		else if (it->getType() == Token::DIRECTIVE)
		{
			if (it->getString() == "#primitive")
				handlePrimitive(lexerIn, it);
			else
				throw ParseException(ParseException::UNKNOWN_NAME);
		}
		else
			throw ParseException(ParseException::UNEXPECTED_TOKEN, *it);
	}
}
