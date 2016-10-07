#include "Word.h"

void Word::setAlias()
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
	alias = "u_" + cleanName;
}

Word::Word(const Word::Type& typeIn, const std::string& nameIn, const std::vector<Token>& membersIn) :
	type(typeIn),
	name(nameIn),
	members(membersIn)
{
	setAlias();
}

Word::Word(const Word::Type& typeIn, const std::string& nameIn, const Token& memberIn) :
	type(typeIn),
	name(nameIn)
{
	setAlias();
	members.push_back(memberIn);
}

Word::Word(const Word::Type& typeIn, const std::string& nameIn) :
	type(typeIn),
	name(nameIn)
{
	setAlias();
}

bool Word::contains(const Token& tokenIn) const
{
	if (std::find(begin(), end(), tokenIn) != end())
		return true;
	else
		return false;
}

std::string Word::toString() const
{
	std::string retString = to_string(type) + "<" + name + ">";
	if (!members.empty())
		retString += "[";
	for (auto const & token : members)
	{
		retString += "\n\t" + token.toString();
	}
	if (!members.empty())
		retString += "\n]";
	return retString;
}

std::ostream& operator<<(std::ostream& outstream, const Word& word)
{
	outstream << word.toString();
	return outstream;
}

std::ostream& operator<<(std::ostream& outstream, const Word::Type& type)
{
	return outstream << to_string(type);
}

std::string to_string(const Word::Type& type)
{
	switch (type)
	{
	case Word::Type::FUNCTION:	return "FUNCTION"; break;
	case Word::Type::VARIABLE:	return "VARIABLE"; break;
	case Word::Type::CONSTANT:	return "CONSTANT"; break;
	case Word::Type::ARRAY:		return "ARRAY"; break;
	default:					return "INVALID_WORD";
	}
}

Word::Type operator|(const Word::Type& a, const Word::Type& b)
{
	return static_cast<Word::Type>(static_cast<int>(a) | static_cast<int>(b));
}

Word::Type operator&(const Word::Type& a, const Word::Type& b)
{
	return static_cast<Word::Type>(static_cast<int>(a) & static_cast<int>(b));
}