#include "Word.h"

Word::Word(const Word::Type& typeIn, const std::string& nameIn, const std::vector<Token>& membersIn, int flagsIn) :
	type(typeIn),
	name(nameIn),
	members(membersIn),
	flags(flagsIn)
{}

Word::Word(const Word::Type& typeIn, const std::string& nameIn, const Token& memberIn, int flagsIn) :
	type(typeIn),
	name(nameIn),
	flags(flagsIn)
{
	members.push_back(memberIn);
}

Word::Word(const Word::Type& typeIn, const std::string& nameIn, int flagsIn) :
	type(typeIn),
	name(nameIn),
	flags(flagsIn)
{}

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