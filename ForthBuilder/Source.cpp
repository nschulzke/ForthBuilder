#include "Lexer.h"
#include "Parser.h"
#include "FileIO.h"
#include <iostream>

int main()
{
	try
	{
		std::string workingDir = "D:\\School\\Fall 2016\\CS 2810\\Final Project\\FORTH Compiler\\Test Files\\";
		std::string outputDir = "D:\\School\\Fall 2016\\CS 2810\\Final Project\\FORTH Compiler\\Test Files\\Output\\";
		std::string inFile = "primitives.asm";
		std::string outFile = "test.asm";

		FileIO fileManager(workingDir, outputDir);
		Lexer tokenizer(inFile, &fileManager);
		Parser parser(tokenizer);

		std::cout << "WORDS:" << std::endl;
		for (auto const & word : parser.wordList())
		{
			std::cout << word << std::endl;
		}

		std::cout << "PRIMITIVES:" << std::endl;
		for (auto const & primitive : parser.primitiveList())
		{
			std::cout << primitive << std::endl;
		}

		system("PAUSE");
	}
	catch (ParseException &e)
	{
		std::cout << e.what() << std::endl;

		system("PAUSE");
	}
	catch (IOException &e)
	{
		std::cout << e.what() << std::endl;

		system("PAUSE");
	}
}