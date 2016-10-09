#pragma once

#include <vector>
#include "Token.h"
#include "ParseException.h"
#include "boost/algorithm/string.hpp"

const int FLAG1 = 1;
const int FLAG2 = 2;
const int FLAG3 = 4;

class Word
{
public:
	enum Type {
		INVALID_WORD = 0,
		FUNCTION = 1,
		VARIABLE = 2,
		CONSTANT = 4,
		ARRAY = 8,
	};
private:
	Type type;
	std::string name;
	std::vector<Token> members;
	int flags;
public:
	Word(const Word::Type& typeIn, const std::string& nameIn, const std::vector<Token>& membersIn, int flagsIn = 0);
	Word(const Word::Type& typeIn, const std::string& nameIn, const Token& memberIn, int flagsIn = 0);
	Word(const Word::Type& typeIn, const std::string& nameIn, int flagsIn = 0);

	std::vector<Token>::const_iterator begin() const { return members.begin(); };
	std::vector<Token>::const_iterator end() const { return members.end(); };
	bool contains(const Token& tokenIn) const;
	// Returns the string representation of the word
	std::string toString() const;
	std::string getName() const { return name; };
	Type getType() const { return type; };
	int getFlags() const { return flags; };

	// Defines the insertion operator for the Word class
	friend std::ostream& operator<<(std::ostream& outstream, const Word& word);

	// Overloads the insertion operator for Word::Type objects
	friend std::ostream& operator<<(std::ostream& outstream, const Word::Type& token);
	// toString function for Word::Type enum
	friend std::string to_string(const Word::Type& type);
	// Overloads the OR operator so they can be combined (A | B)
	friend Word::Type operator|(const Word::Type& a, const Word::Type& b);
	// Overloads the AND operator so we can compare ((A | B) & (B | C) = B)
	friend Word::Type operator&(const Word::Type& a, const Word::Type& b);
};

