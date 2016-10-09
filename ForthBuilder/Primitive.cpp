#include "Primitive.h"

std::string Primitive::toString() const
{
	std::string retString = "PRIMITIVE( " + name + " : " + label + " )";
	if (flags != 0)
		retString += " flags:" + flags;
	return retString;
}

std::ostream& operator<<(std::ostream& outstream, const Primitive& primitive)
{
	outstream << primitive.toString();
	return outstream;
}