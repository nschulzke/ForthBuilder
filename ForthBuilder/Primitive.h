#pragma once

#include <string>
#include "Token.h"

class Primitive
{
private:
	std::string name;
	std::string label;
	int flags;
public:
	Primitive(const std::string &nameIn, const std::string &labelIn, int flagsIn = 0) :
		name(nameIn),
		label(labelIn),
		flags(flagsIn)
	{};

	std::string toString() const;
	std::string getName() const { return name; };
	std::string getLabel() const { return label; };
	int getFlags() const { return flags; };

	// Defines the insertion operator for the Primitive class
	friend std::ostream& operator<<(std::ostream& outstream, const Primitive& word);
};

