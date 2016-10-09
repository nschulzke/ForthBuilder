#pragma once

#include "Word.h"
#include "Primitive.h"
#include <string>
#include <vector>

class Entry
{
private:
	const Entry* link;
	std::string name;
	std::string alias;
	int nameLength;
	int flags;
	std::vector<Token> tokens;

	std::string setAlias(const std::string& nameIn);
	void processTokens(const Word & wordIn);
public:
	Entry(const Word &wordIn, const Entry* linkIn);
	Entry(const Primitive &primIn, const Entry* linkIn);
};

