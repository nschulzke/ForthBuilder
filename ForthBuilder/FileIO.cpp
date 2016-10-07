#include "FileIO.h"

typedef boost::escaped_list_separator<char> separator;

// These ought to be set by the main program
void FileIO::load(const std::string &fileNameIn, std::vector<std::string> &vectorOut)
{
	std::ifstream inFile;
	std::string inString = "";

	inFile.open(workingDir + fileNameIn);
	if (inFile.good())
	{
		includedFiles.push_back(fileNameIn);
		while (getline(inFile, inString)) {
			if (inString.find("#include") == std::string::npos)		// If the line isn't an #include
				vectorOut.push_back(inString);						// then add it to the return vector
			else
				addIncludes(inString, vectorOut);
		}
	} // end if inFile.good()
	else
		throw IOException(IOException::Code::READ_ERROR, fileNameIn);
	inFile.close();
	includedFiles.clear();
}

std::vector<std::string> FileIO::load(const std::string &fileNameIn)
{
	std::vector<std::string> retVector;
	load(fileNameIn, retVector);
	return retVector;
}

void FileIO::addIncludes(const std::string &includeLine, std::vector<std::string> &inLines)
{
	std::string inString = includeLine;
	boost::replace_first(inString, "#include", "");
	boost::tokenizer<separator> tokenize(inString, separator("\\", ", \t", "\"\'"));	// Separate by comma, space, or tab, with " or ' quoting

	std::string fileName;				// Hold the file names that we find
	for (auto const & token : tokenize)
	{
		if (token != "")				// Some tokens will be empty if there are several spaces. Skip those
		{
			fileName = token;
			boost::replace_all(fileName, "\"", "");		// Remove quotes from the final filename before loading it

			if (std::find(includedFiles.begin(), includedFiles.end(), fileName) == includedFiles.end())
				load(fileName, inLines);
		}
	}

}

void FileIO::write(const std::string &path, std::vector<std::string> &outLines)
{
	std::ofstream outFile;

	outFile.open(outputDir + path);
	if (outFile.good())
		for (auto const & line : outLines)
			outFile << line << std::endl;
	else
		throw IOException(IOException::Code::WRITE_ERROR, path);
	outFile.close();
}

void FileIO::append(const std::string &path, std::vector<std::string> &outLines)
{
	std::ofstream outFile;

	outFile.open(outputDir + path, std::ios_base::app);
	if (outFile.good())
		for (auto const & line : outLines)
			outFile << line << std::endl;
	else
		throw IOException(IOException::Code::WRITE_ERROR, path);
	outFile.close();
}