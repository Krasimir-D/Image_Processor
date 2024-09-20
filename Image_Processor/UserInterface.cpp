#include "UserInterface.h"
#include "CommandFactory.hpp"
#include "CommandLine.h"

UserInterface& UserInterface::getInstance()
{
	static UserInterface instance;
	return instance;
}

void UserInterface::run()
{
	printHelp();
	while (isRunning)
	{
		try
		{
			std::cout << "> ";
			std::string commandLine;
			std::getline(std::cin, commandLine);
			// splits the command into arguments 
			std::vector<std::string> arguments = CommandLine::parseCommandLine(commandLine);
			// first we try to create a system command because they have a bigger priority over the image altering commands
			SystemCommand* sysCmd = CommandFactory::getFactory().createSystemCommand(arguments);
			// at some point load and exit will no longer be system commands, but a separate type, which operates on the UI itself, not on the a session object
			// so dynamic casting won't be neccessary 
			if (sysCmd)
			{
				// load is a special type of system command because it does not affect a session, it creates it
				if (dynamic_cast<Load*>(sysCmd))
				{
					// close the previous session if one exists and display "unsaved work" dialog
					if (sessions.size() > 0)
					{
						if (sessions[activeSessionIndex].getHasUsavedProgress())
							sessions[activeSessionIndex].displayUnsavedProgressDialog();
					}

					Session newSession;
					(*sysCmd)(newSession); // executes the load commands
					// move-copies the object so the destructor isn't called on the dynamically allocated objects
					sessions.push_back(std::move(newSession));
					activeSessionIndex = sessions.size() - 1;					
				}
				// exit is a special type of system command because it terminates the program
				else if (dynamic_cast<Exit*>(sysCmd))
				{
					if ((activeSessionIndex >= 0) && sessions[activeSessionIndex].getHasUsavedProgress())
						sessions[activeSessionIndex].displayUnsavedProgressDialog();
					else					
						sessions[activeSessionIndex].save();			
					
					isRunning = false;
				}

				else if (activeSessionIndex < 0)
					std::cout << "> No active session currently. Load command expected!" << std::endl;

				else
					(*sysCmd)(sessions[activeSessionIndex]);

				// on to the next loop.
				continue;
			}
			// system commands do not get stored or used after their creation, therefore they get deleted here
			delete sysCmd;

			// if no system command was created, try creating an image command
			ImageCommand* imgCmd = CommandFactory::getFactory().createImageCommand(arguments);
			if (imgCmd)
			{
				if (activeSessionIndex < 0)
				{
					std::cout << "> No active session currently. Load command expected!" << std::endl;
					continue;
				}

				sessions[activeSessionIndex].handleCommand(imgCmd);
				continue;
			}

			// if neither a system command nor an image command was created notify user
			else
				std::cout << "> Command not recognized!" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}		
	}	
}


void UserInterface::printHelp() const
{
	std::cout << "> The following commands are supported:" << std::endl;
	std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
	std::cout << "> load <path1> <path2> ..." << std::endl;
	std::cout << "> save" << std::endl;
	std::cout << "> saveas <path1> <path2> ..." << std::endl;
	std::cout << "> list session" << std::endl;
	std::cout << "> add <path>" << std::endl;
	std::cout << "> crop <(x,y) for top-left corner> <(x,y) for bottom-right corner>" << std::endl;
	std::cout << "> monochrome" << std::endl;
	std::cout << "> grayscale" << std::endl;
	std::cout << "> negative" << std::endl;
	std::cout << "> rotate left" << std::endl;
	std::cout << "> rotate right" << std::endl;
	std::cout << "> flip top" << std::endl;
	std::cout << "> flip left" << std::endl;
	std::cout << "> undo" << std::endl;
	std::cout << "> redo" << std::endl;
	std::cout << "> make collage <path1> <path2> <orientation (vertical/ horizontal)>" << std::endl;
	std::cout << "> exit" << std::endl << std::endl;	
}

UserInterface::UserInterface()
	: isRunning(true), activeSessionIndex(-1)
{}
