#include "Parser.h"

#include "boost/algorithm/string.hpp"

void Parser::ignoreComment(const Lexer* lexerIn, std::vector<Token>::const_iterator& it)
{
	if (it + 1 < lexerIn->end())
	{
		it++;
		bool foundEnd = false;
		for (it; it < lexerIn->end(); it++)
		{
			if (it->getType() == Token::WORD && it->getString() == ")")
			{
				foundEnd = true;
				break;
			}
		}
		if (!foundEnd && it == lexerIn->end())
		{
			it--;
			throw ParseException(ParseException::UNEXPECTED_EOF, *it);
		}
	}
}

Parser::Parser(const Lexer * lexerIn)
{
	parse(lexerIn);
}

void Parser::parse(const Lexer* lexerIn)
{
	for (std::vector<Token>::const_iterator it = lexerIn->begin(); it < lexerIn->end(); it++)
	{
		if (it->getType() == Token::WORD)
		{
			if (it->getString() == ":")
			{
				std::vector<Token> tokens;
				if (it + 1 < lexerIn->end())
				{
					it++;
					std::string name = it->getString();
					if (it + 1 < lexerIn->end())
					{
						it++;
						for (it; it < lexerIn->end(); it++)
						{
							if (it->getString() == "(")
							{
								ignoreComment(lexerIn, it);
							}
							else if (it->getType() == Token::WORD && it->getString() == ";")
							{
								words.push_back(Word(Word::FUNCTION, name, tokens));
								tokens.clear();
								break;
							}
							else
							{
								tokens.push_back(*it);
							}
						}
						if (!tokens.empty() && it == lexerIn->end())
						{
							it--;
							throw ParseException(ParseException::UNEXPECTED_EOF, *it);
						}
					}
					else
						throw ParseException(ParseException::UNEXPECTED_EOF, *it);
				}
			}
			else if (it->getString() == "(")
			{
				ignoreComment(lexerIn, it);
			}
			else if (it->getString() == "VARIABLE")
			{
				if (it + 1 < lexerIn->end())
				{
					it++;
					if (it->getType() == Token::WORD)
						words.push_back(Word(Word::VARIABLE, it->getString()));
					else
						throw ParseException(ParseException::EXPECTED_WORD, *it);
				}
				else
					throw ParseException(ParseException::UNEXPECTED_EOF, *it);
			}
			else
				throw ParseException(ParseException::EXPECTED_DEF_WORD, *it);
		}
		else if (it->getType() == Token::NUMBER)
		{
			Token temp = *it;
			if (it + 1 < lexerIn->end())
			{
				it++;
				if (it->getType() == Token::WORD && it->getString() == "CONSTANT")
				{
					if (it + 1 < lexerIn->end())
					{
						it++;
						if (it->getType() == Token::WORD)
							words.push_back(Word(Word::CONSTANT, it->getString(), temp));
						else
							throw ParseException(ParseException::EXPECTED_WORD, *it);
					}
					else
						throw ParseException(ParseException::UNEXPECTED_EOF, *it);
				}
				else
				{
					throw ParseException(ParseException::EXPECTED_DEF_WORD, *it);
				}
			}
			else
				throw ParseException(ParseException::UNEXPECTED_EOF, *it);
		}
		else
		{
			throw ParseException(ParseException::EXPECTED_DEF_WORD, *it);
		}
	}
}