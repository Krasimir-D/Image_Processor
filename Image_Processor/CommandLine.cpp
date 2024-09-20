#include "CommandLine.h"
#include <iomanip>
#include <cmath>
#include <sstream>

unsigned CommandLine::parseInteger(const std::string& str)
{
	size_t length = str.length();
	if (length == 0)
	{
		std::cerr << "String does not contain a number!\n";
		throw std::invalid_argument("String does not contain a number!");
	}
	if (str[0] == '0' && length != 1)
	{
		std::cerr << "A number can not start with 0!\n";
		throw std::invalid_argument("Integer starting with 0!");
	}
	unsigned result = 0;
	unsigned mult = static_cast<unsigned>(std::pow(10, length - 1));

	for (size_t i = 0; i < length; i++)
	{
		if (!isDigit(str[i]))
		{
			std::cerr << "Invalid number!\n";
			throw std::invalid_argument("Invalid number!");
		}

		result += (str[i] - '0') * mult;
		mult /= 10;
	}

	return result;
}

bool CommandLine::isDigit(char c)
{
	return (c > 47) && (c < 58);
}

std::string CommandLine::removeExtraWhitespaces(const std::string& string)
{
	size_t length = string.length();
	std::string result = "";
	bool isPrevWhitespace = false;

	for (size_t i = 0; i < length; i++)
	{
		if (string[i] != ' ' && isPrevWhitespace)
		{
			result.push_back(string[i]);
			isPrevWhitespace = false;
			continue;
		}

		if (string[i] == ' ' && isPrevWhitespace)
			continue;

		if (string[i] == ' ' && !isPrevWhitespace)
		{
			result.push_back(string[i]);
			isPrevWhitespace = true;
			continue;
		}

		if (string[i] == ' ' && i == length - 1)
			break;

		result.push_back(string[i]);
	}

	return result;
}

std::string CommandLine::stringToLower(const std::string& string) 
{
	size_t length = string.length();
	std::string result = string;
	for (size_t i = 0; i < length; i++)
	{
		if (result[i] > 64 && result[i] < 91)
			result[i] += 32;
	}
	return result;
}

std::vector<std::string> CommandLine::parseCommandLine(const std::string& string)
{
	std::string result = CommandLine::removeExtraWhitespaces(string);
	std::string currentWord;
	size_t length = result.length();
	std::vector<std::string> arguments;

	for (size_t i = 0; i < length; i++)
	{
		if (result[i] == ' ')
		{
			arguments.push_back(currentWord);
			currentWord = "";
			continue;
		}

		if (result[i] != ' ' && i == length)
		{
			currentWord.push_back(result[i]);
			arguments.push_back(currentWord);
			currentWord = "";
		}

		else
			currentWord.push_back(result[i]);
	}
	arguments.push_back(currentWord);
	removeEmptyArguments(arguments);

	return arguments;
}

void CommandLine::removeEmptyArguments(std::vector<std::string>& arguments)
{
	size_t size = arguments.size();
	for (size_t i = 0; i < size; i++)
	{
		if (arguments[i] == "")
		{
			arguments.erase(arguments.begin() + i);
			i--;
		}
	}
}

std::string CommandLine::removeFileExtension(const std::string& path)
{	
	size_t length = path.length();
	size_t i = path.rfind('.');
	
	// no extension found
	if (i == std::string::npos)
		return path;

	return path.substr(0, i);
}

std::string CommandLine::extractFileExtension(const std::string& path)
{
	std::string result = "";
	// finds the index of the last occurence of '.' because an extension is expected after it
	size_t dotIndex = path.rfind('.');

	for (size_t i = dotIndex + 1; i < path.length(); i++)
	{
		result += path[i];
	}

	return result;
}

std::string CommandLine::getCurrentTimestamp()
{
	auto now = std::time(nullptr);
	std::tm tm;
	localtime_s(&tm, &now); // For Windows

	std::ostringstream oss;
	oss << std::put_time(&tm, "_%Y_%m_%d");
	return oss.str();
}

std::string CommandLine::timestampFilePath(const std::string& path)
{
	// Find the last dot in the file path
	size_t lastDot = path.rfind('.');

	if (lastDot == std::string::npos)
	{
		// No extension found
		return path + getCurrentTimestamp();
	}

	// Extract file name and extension
	std::string fileName = path.substr(0, lastDot);
	std::string extension = path.substr(lastDot);

	// Get the current timestamp
	std::string timestamp = getCurrentTimestamp();

	// Construct the new file path with timestamp
	std::string newFilePath = fileName + timestamp + extension;
	return newFilePath;
}





