#include "Entry.h"

Entry::Entry(const Word &wordIn, const Entry* linkIn)
{
	link = linkIn;
	name = wordIn.getName();
	alias = setAlias(name);
	nameLength = name.length();
	processTokens(wordIn);
	int flags = wordIn.getFlags();
}

Entry::Entry(const Primitive &primIn, const Entry* linkIn)
{
	link = linkIn;
	name = primIn.getName();
	alias = primIn.getLabel();
	nameLength = name.length();
	tokens.push_back(Token(alias, Token::PRIMITIVE));
	int flags = primIn.getFlags();
}

void Entry::processTokens(const Word & wordIn)
{
	for (auto const &token : wordIn)
	{
		if (token.getType() == Token::NUMBER)
		{
			tokens.push_back(Token("LIT"));
			tokens.push_back(token);
		}
		else
			tokens.push_back(token);
	}
}

std::string Entry::setAlias(const std::string& nameIn)
{
	std::string cleanName = name;
	boost::replace_all(cleanName, "~", "tild");
	boost::replace_all(cleanName, "`", "btck");
	boost::replace_all(cleanName, "*", "star");
	boost::replace_all(cleanName, "!", "excl");
	boost::replace_all(cleanName, "@", "at");
	boost::replace_all(cleanName, "#", "lb");
	boost::replace_all(cleanName, "$", "dol");
	boost::replace_all(cleanName, "%", "pcnt");
	boost::replace_all(cleanName, "^", "crt");
	boost::replace_all(cleanName, "&", "amp");
	boost::replace_all(cleanName, "*", "star");
	boost::replace_all(cleanName, "(", "lprn");
	boost::replace_all(cleanName, ")", "rprn");
	boost::replace_all(cleanName, "-", "dash");
	boost::replace_all(cleanName, "{", "lbrc");
	boost::replace_all(cleanName, "}", "rbrc");
	boost::replace_all(cleanName, "[", "lbrk");
	boost::replace_all(cleanName, "]", "rbrk");
	boost::replace_all(cleanName, ";", "semi");
	boost::replace_all(cleanName, ":", "colo");
	boost::replace_all(cleanName, "\"", "quot");
	boost::replace_all(cleanName, "'", "tick");
	boost::replace_all(cleanName, "<", "less");
	boost::replace_all(cleanName, ">", "more");
	boost::replace_all(cleanName, ",", "comm");
	boost::replace_all(cleanName, ".", "dot");
	boost::replace_all(cleanName, "?", "ques");
	boost::replace_all(cleanName, "/", "slsh");
	boost::replace_all(cleanName, "|", "pipe");
	boost::replace_all(cleanName, "\\", "whac");
	return cleanName;
}