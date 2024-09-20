#pragma once
#include "CommandLine.h"

class Session;
// commands that dont affect an image directly. logically distinct from the ImageCommands
class SystemCommand
{
public:
	SystemCommand(const std::string& name);
	virtual SystemCommand* clone() const = 0;
	virtual ~SystemCommand() = default;

	const std::string& getName() const;
	void operator()(Session& session);

private:
	virtual void execute(Session& session) const = 0;

protected:
	const std::string name;
};

class Load : public SystemCommand
{
public:
	Load(const std::vector<std::string>& paths);
	virtual SystemCommand* clone() const override;

	const std::vector<std::string>& getPaths() const;

private:
	virtual void execute(Session& session) const override;

private:
	const std::vector<std::string> paths;
};

class Save : public SystemCommand
{
public:
	Save();
	virtual SystemCommand* clone() const override;

private:
	virtual void execute(Session& session) const override;
};

class Saveas : public SystemCommand
{
public:
	Saveas(const std::vector<std::string>& paths);
	virtual SystemCommand* clone() const override;

	const std::vector<std::string> getPaths() const;

private:
	virtual void execute(Session& session) const override;

private:
	const std::vector<std::string> paths;
};

class ListSession : public SystemCommand
{
public:
	ListSession();
	virtual SystemCommand* clone() const override;

private:
	virtual void execute(Session& session) const override;
};

class Undo : public SystemCommand
{
public:
	Undo();
	virtual SystemCommand* clone() const override;

private:
	virtual void execute(Session& session) const override;
};

class Redo : public SystemCommand
{
public:
	Redo();
	virtual SystemCommand* clone() const override;

private:
	virtual void execute(Session& session) const override;
};

class Add : public SystemCommand
{
public:
	Add(const std::string& path);
	virtual SystemCommand* clone() const override;
	const std::string& getPath() const;

private:
	virtual void execute(Session& session) const override;
	const std::string& path;
};

class MakeCollage : public SystemCommand
{
public:
	MakeCollage(const std::string& img1, const std::string& img2, bool orientation);
	virtual SystemCommand* clone() const override;
	bool getOrientation() const;

private:
	virtual void execute(Session& session) const override;
	const std::string img1;
	const std::string img2;
	const bool orientation;
};

class Exit : public SystemCommand
{
public:
	Exit();
	virtual SystemCommand* clone() const override;

private:
	virtual void execute(Session& session) const override;
};