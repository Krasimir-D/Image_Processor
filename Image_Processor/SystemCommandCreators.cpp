#include "SystemCommandCreators.h"
#include "CommandFactory.hpp"

SystemCommandCreator::SystemCommandCreator(const std::string& name)
	: name(name)
{
	CommandFactory::getFactory().registerSystemCommand(this);
}

bool SystemCommandCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	std::string temp = arguments[0];
	temp = CommandLine::stringToLower(temp);
	return temp == name;
}

SystemCommandCreator* LoadCreator::clone() const
{
	return new LoadCreator(*this);
}

bool LoadCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 2)
		return false;

	return SystemCommandCreator::isIdenticalCommand(arguments);
}

SystemCommand* LoadCreator::createCommand(const std::vector<std::string>& arguments) const
{
	std::vector<std::string> paths;
	for (size_t i = 1; i < arguments.size(); i++)
	{
		paths.push_back(arguments[i]);
	}

	return new Load(paths);
}

SystemCommandCreator* SaveCreator::clone() const
{
	return new SaveCreator(*this);
}

bool SaveCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() != 1)
		return false;

	return SystemCommandCreator::isIdenticalCommand(arguments);
}

SystemCommand* SaveCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Save();
}

SystemCommandCreator* SaveasCreator::clone() const
{
	return new SaveasCreator(*this);
}

bool SaveasCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() < 1)
		return false;

	return SystemCommandCreator::isIdenticalCommand(arguments);
}

SystemCommand* SaveasCreator::createCommand(const std::vector<std::string>& arguments) const
{
	std::vector<std::string> paths;
	for (size_t i = 1; i < arguments.size(); i++)
	{
		paths.push_back(arguments[i]);
	}

	return new Saveas(paths);
}

SystemCommandCreator* ListSessionCreator::clone() const
{
	return new ListSessionCreator(*this);
}

bool ListSessionCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() != 2)
		return false;

	std::string temp = arguments[0] + " " + arguments[1];
	temp = CommandLine::stringToLower(temp);
	return temp == name;
}

SystemCommand* ListSessionCreator::createCommand(const std::vector<std::string>& paths) const
{
	return new ListSession();
}

SystemCommandCreator* UndoCreator::clone() const
{
	return new UndoCreator(*this);
}

bool UndoCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() != 1)
		return false;

	return SystemCommandCreator::isIdenticalCommand(arguments);
}

SystemCommand* UndoCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Undo();
}

SystemCommandCreator* RedoCreator::clone() const
{
	return new RedoCreator(*this);
}

bool RedoCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() != 1)
		return false;

	return SystemCommandCreator::isIdenticalCommand(arguments);
}

SystemCommand* RedoCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Redo();
}

SystemCommandCreator* AddCreator::clone() const
{
	return new AddCreator(*this);
}

bool AddCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if(arguments.size() != 2)
		return false;

	return SystemCommandCreator::isIdenticalCommand(arguments);
}

SystemCommand* AddCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Add(arguments[1]);
}

SystemCommandCreator* ExitCreator::clone() const
{
	return new ExitCreator(*this);
}

bool ExitCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if(arguments.size() != 1)
		return false;

	return SystemCommandCreator::isIdenticalCommand(arguments);
}

SystemCommand* ExitCreator::createCommand(const std::vector<std::string>& arguments) const
{
	return new Exit();
}

SystemCommandCreator* MakeCollageCreator::clone() const
{
	return new MakeCollageCreator(*this);
}

bool MakeCollageCreator::isIdenticalCommand(const std::vector<std::string>& arguments) const
{
	if (arguments.size() != 5)
		return false;

	// guaranteed foolprofing considering case- sensitivity
	std::string temp = arguments[0] + " " + arguments[1];
	temp = CommandLine::stringToLower(temp);
	std::string tempOrientation = CommandLine::stringToLower(arguments[4]);

	return (temp == name) && (tempOrientation == ORIENTATION_HORIZONTAL || tempOrientation == ORIENTATION_VERTICAL);
}

SystemCommand* MakeCollageCreator::createCommand(const std::vector<std::string>& arguments) const
{
	std::string tempOrientation = CommandLine::stringToLower(arguments[4]);
	bool aggregatedOrientation = (tempOrientation == ORIENTATION_VERTICAL) ? 0 : 1;
	return new MakeCollage(arguments[2], arguments[3], aggregatedOrientation);
}

static LoadCreator __1;
static SaveCreator __2;
static SaveasCreator __3;
static ListSessionCreator __4;
static UndoCreator __5;
static RedoCreator __6;
static AddCreator __7;
static MakeCollageCreator __8;
static ExitCreator __9;