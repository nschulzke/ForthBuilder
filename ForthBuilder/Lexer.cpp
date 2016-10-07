#include "Lexer.h"

Lexer::Lexer(const std::string &fileNameIn, FileIO* fileManagerIn) :
	fileManager(fileManagerIn)
{
	lex(fileNameIn);
};

void Lexer::split(const std::string &stringIn, char delimIn, std::vector<std::string> &elemsIn)
{
	std::stringstream stream;
	stream.str(stringIn);
	std::string item;
	while (std::getline(stream, item, delimIn)) {
		elemsIn.push_back(item);
	}
}

void Lexer::split(char delimIn, std::vector<std::string> &elemsIn)
{
	std::vector<std::string> newVector;
	for (auto const & elem : elemsIn)
	{
		split(elem, delimIn, newVector);
	}
	elemsIn = newVector;
}

std::vector<std::string> Lexer::split(const std::string &stringIn)
{
	std::vector<std::string> elemsOut;
	split(stringIn, '\t', elemsOut);
	split(' ', elemsOut);
	return elemsOut;
}

void Lexer::lex(const std::string &fileNameIn)
{
	std::vector<std::string> loadVector = fileManager->load(fileNameIn);

	for (auto const & line : loadVector)
	{
		std::vector<std::string> tempVector = split(line);
		for (auto const & splitString : tempVector)
		{
			tokens.push_back(splitString);
		}
		tempVector.clear();
	}
}
