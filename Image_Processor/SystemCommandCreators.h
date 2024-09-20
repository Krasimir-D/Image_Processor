#pragma once
#include "SystemCommand.h"

class SystemCommandCreator
{
public:
	SystemCommandCreator(const std::string& name); // defines the type of SystemCommand that will be created based on the console input
	virtual ~SystemCommandCreator() = default;
	virtual SystemCommandCreator* clone() const = 0;

	// Checkes whether the SystemCommand at input matches the current SystemCommand type
	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const = 0;

protected:
	const std::string name;
};

class LoadCreator : public SystemCommandCreator
{
public:
	LoadCreator() : SystemCommandCreator("load") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class SaveCreator : public SystemCommandCreator
{
public:
	SaveCreator() : SystemCommandCreator("save") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class SaveasCreator : public SystemCommandCreator
{
public:
	SaveasCreator() : SystemCommandCreator("saveas") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class ListSessionCreator : public SystemCommandCreator
{
public:
	ListSessionCreator() : SystemCommandCreator("list session") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& paths) const override;
};

class UndoCreator : public SystemCommandCreator
{
public:
	UndoCreator() : SystemCommandCreator("undo") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class RedoCreator : public SystemCommandCreator
{
public:
	RedoCreator() : SystemCommandCreator("redo") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class AddCreator : public SystemCommandCreator
{
public:
	AddCreator() : SystemCommandCreator("add") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class MakeCollageCreator : public SystemCommandCreator
{
public:
	MakeCollageCreator() : SystemCommandCreator("make collage") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const override;

private:
	static constexpr const char ORIENTATION_HORIZONTAL[] = "horizontal";
	static constexpr const char ORIENTATION_VERTICAL[] = "vertical";
};

class ExitCreator : public SystemCommandCreator
{
public:
	ExitCreator() : SystemCommandCreator("exit") {}
	virtual SystemCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector <std::string>& arguments) const override;
	virtual SystemCommand* createCommand(const std::vector<std::string>& arguments) const override;
};