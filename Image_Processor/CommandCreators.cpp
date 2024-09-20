#include "ImageCommandCreators.h"
#include "CommandFactory.hpp"

ImageCommandCreator::ImageCommandCreator(const std::string& name)
	: name(name)
{
	CommandFactory::getFactory().registerImageCommand(this);
}

bool ImageCommandCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	std::string temp = arguments[0];
	temp = CommandLine::stringToLower(temp);
	return temp == name;
}

ImageCommandCreator* CropCreator::clone() const
{
	return new CropCreator(*this);
}

bool CropCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 5)
		return false;

	return ImageCommandCreator::isIdenticalCommand(arguments);
}

ImageCommand* CropCreator::createCommand(const std::vector<std::string>& arguments) const
{
	unsigned top_left_x = CommandLine::parseInteger(arguments[1]);
	unsigned top_left_y = CommandLine::parseInteger(arguments[2]);
	unsigned bottom_right_x = CommandLine::parseInteger(arguments[3]);
	unsigned bottom_right_y = CommandLine::parseInteger(arguments[4]);

	return new Crop(top_left_x, top_left_y, bottom_right_x, bottom_right_y);
}

ImageCommandCreator* MonochromeCreator::clone() const
{
	return new MonochromeCreator(*this);
}

bool MonochromeCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() != 1)
		return false;

	return ImageCommandCreator::isIdenticalCommand(arguments);;
}

ImageCommand* MonochromeCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Monochrome();
}

ImageCommandCreator* NegativeCreator::clone() const
{
	return new NegativeCreator(*this);
}

bool NegativeCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 1)
		return false;

	return ImageCommandCreator::isIdenticalCommand(arguments);
}

ImageCommand* NegativeCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Negative();
}

ImageCommandCreator* GrayscaleCreator::clone() const
{
	return new GrayscaleCreator(*this);
}

bool GrayscaleCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 1)
		return false;

	return ImageCommandCreator::isIdenticalCommand(arguments);
}

ImageCommand* GrayscaleCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Grayscale();
}

ImageCommandCreator* RotateLeftCreator::clone() const
{
	return new RotateLeftCreator(*this);
}

bool RotateLeftCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 2)
		return false;

	std::string temp = arguments[0] + " " + arguments[1];
	temp = CommandLine::stringToLower(temp);
	return temp == name;
}

ImageCommand* RotateLeftCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new RotateLeft();
}

ImageCommandCreator* RotateRightCreator::clone() const
{
	return new RotateRightCreator(*this);
}

bool RotateRightCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 2)
		return false;

	std::string temp = arguments[0] + " " + arguments[1];
	temp = CommandLine::stringToLower(temp);
	return temp == name;
}

ImageCommand* RotateRightCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new RotateRight();
}

ImageCommandCreator* FlipTopCreator::clone() const
{
	return new FlipTopCreator(*this);
}

bool FlipTopCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 2)
		return false;

	std::string temp = arguments[0] + " " + arguments[1];
	temp = CommandLine::stringToLower(temp);
	return temp == name;
}

ImageCommand* FlipTopCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new FlipTop();
}

ImageCommandCreator* FlipLeftCreator::clone() const
{
	return new FlipLeftCreator(*this);
}

bool FlipLeftCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 2)
		return false;

	std::string temp = arguments[0] + " " + arguments[1];
	temp = CommandLine::stringToLower(temp);
	return temp == name;
}

ImageCommand* FlipLeftCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new FlipLeft();
}

static CropCreator __1;
static MonochromeCreator __2;
static NegativeCreator __3;
static GrayscaleCreator __4;
static RotateLeftCreator __5;
static RotateRightCreator __6;
static FlipTopCreator __7;
static FlipLeftCreator __8;
