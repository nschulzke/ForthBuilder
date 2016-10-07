#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "boost/tokenizer.hpp"
#include "boost/algorithm/string.hpp"
#include "IOException.h"

class FileIO
{
private:
	std::string workingDir;
	std::string outputDir;
	std::vector<std::string> includedFiles;

	/// Takes a line beginning with an #include statement and includes any files that haven't been included yet
	void FileIO::addIncludes(const std::string &includeLine, std::vector<std::string> &inLines);
public:
	FileIO::FileIO(std::string workingDirIn, std::string outputDirIn) :
		workingDir(workingDirIn), outputDir(outputDirIn)
	{};

	void setWorkingDir(const std::string& dirIn) { workingDir = dirIn; };
	void setOutputDir(const std::string& dirIn) { outputDir = dirIn; };

	/// Load from a file into a string vector, delimited by line breaks
	void load(const std::string &path, std::vector<std::string> &vectorOut);

	/// Load from a file into a string vector, delimited by line breaks
	/// Returns: string vector
	std::vector<std::string> load(const std::string &path);

	/// Write to a file from a string vector
	void write(const std::string &path, std::vector<std::string> &outLines);

	/// Append to a file from a string vector
	void append(const std::string &path, std::vector<std::string> &outLines);
};