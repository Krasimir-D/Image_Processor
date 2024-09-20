#pragma once
#include <iostream>
#include <string>
#include <vector>

// handles with user input validation and ensures that program is foolproof
namespace CommandLine
{//TO DO RETURN NEW STRINGS
	// parses unsinged integers
	unsigned parseInteger(const std::string& str);

	bool isDigit(char c);

	// removes consecutive whitespaces
	std::string removeExtraWhitespaces(const std::string& string);

	// ensures case insensitivity
	std::string stringToLower(const std::string& string);

	// parses the ImageCommand line into arguments
	std::vector<std::string> parseCommandLine(const std::string& string);

	void removeEmptyArguments(std::vector<std::string>& arguments);

	std::string removeFileExtension(const std::string& path);
	std::string extractFileExtension(const std::string& path);

	// helpers for save
	std::string getCurrentTimestamp();
	std::string timestampFilePath(const std::string& path);
};

