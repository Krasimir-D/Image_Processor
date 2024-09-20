#include "SystemCommand.h"
#include "Session.h"
#include "ImageIOFactory.hpp"

SystemCommand::SystemCommand(const std::string& name)
	: name(name)
{}

const std::string& SystemCommand::getName() const
{
	return name;
}

void SystemCommand::operator()(Session& session)
{
	 execute(session);
}

Load::Load(const std::vector<std::string>& paths)
	: SystemCommand("load"), paths(paths)
{
}

SystemCommand* Load::clone() const
{
	return new Load(*this);
}

const std::vector<std::string>& Load::getPaths() const
{
	return paths;
}

void Load::execute(Session& session) const
{
	size_t pathsCount = paths.size();
	for (size_t i = 0; i < pathsCount; i++)
	{
		session.add(paths[i]);
	}
}

Save::Save()
	: SystemCommand("save")
{
}

SystemCommand* Save::clone() const
{
	return new Save(*this);
}

void Save::execute(Session& session) const
{
	session.save();
}

Saveas::Saveas(const std::vector<std::string>& paths)
	: SystemCommand("saveas"), paths(paths)
{
}

SystemCommand* Saveas::clone() const
{
	return new Saveas(*this);
}

const std::vector<std::string> Saveas::getPaths() const
{
	return paths;
}

void Saveas::execute(Session& session) const
{
	session.saveas(paths);
}

ListSession::ListSession()
	: SystemCommand("list session")
{
}

SystemCommand* ListSession::clone() const
{
	return new ListSession(*this);
}

void ListSession::execute(Session& session) const
{
	session.listSession();
}

Undo::Undo()
	: SystemCommand("undo")
{
}

SystemCommand* Undo::clone() const
{
	return new Undo(*this);
}

void Undo::execute(Session& session) const
{
	session.undo();
}

Redo::Redo()
	: SystemCommand("redo")
{
}

SystemCommand* Redo::clone() const
{
	return new Redo(*this);
}

void Redo::execute(Session& session) const
{
	session.redo();
}

Add::Add(const std::string& path)
	: SystemCommand("add"), path(path)
{
}

SystemCommand* Add::clone() const
{
	return new Add(*this);
}

const std::string& Add::getPath() const
{
	return path;
}

void Add::execute(Session& session) const
{
	session.add(path);
}

Exit::Exit()
	: SystemCommand("exit")
{
}

SystemCommand* Exit::clone() const
{
	return new Exit(*this);
}

void Exit::execute(Session& session) const
{
	session.displayUnsavedProgressDialog();
}

MakeCollage::MakeCollage(const std::string& img1, const std::string& img2, bool orientation)
	: SystemCommand("make collage"), img1(img1), img2(img2), orientation(orientation)
{
}

SystemCommand* MakeCollage::clone() const
{
	return new MakeCollage(*this);
}

bool MakeCollage::getOrientation() const
{
	return orientation;
}

void MakeCollage::execute(Session& session) const
{
	session.makeCollage(img1, img2, orientation);
}
