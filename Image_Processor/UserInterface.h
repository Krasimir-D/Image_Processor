#pragma once
#include "Session.h"

class UserInterface
{
public:
	static UserInterface& getInstance();
	void run();
	void printHelp() const;

private:
	UserInterface();
	UserInterface(const UserInterface& other) = delete;
	UserInterface& operator=(const UserInterface & other) = delete;
	~UserInterface() = default;	

private:
	std::vector<Session> sessions;
	size_t activeSessionIndex;
	bool isRunning;
};

