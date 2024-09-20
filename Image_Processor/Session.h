#pragma once
#include "CommandFactory.hpp"
#include "Image.h"

class Session
{
public:
	Session();
	Session(Session&& other) noexcept;
	Session& operator=(Session&& other) noexcept;
	~Session();
	void handleCommand(ImageCommand* cmd);
	void listSession() const;

	// system commands functionalities
	void add(const std::string& path);
	void save();
	void saveas(const std::vector<std::string>& paths);
	void undo();
	void redo();
	void listSession();
	// if orientation == 0 -> vertical. if orientation == 1 -> horizontal
	// produces a collage with path: path1_path2.extension so beware of errors
	void makeCollage(const std::string& path1, const std::string& path2, bool orientation);

	void setIsActive(bool val);
	// getters for private fields
	bool getIsActive() const;
	bool getHasUsavedProgress() const;
	
	void print() const;
	void clearCommands();
	void clearImages();
	void displayUnsavedProgressDialog();

// under the bonnet functionalities
private:	
	// executes all the queued commands and flushes the commands container
	void executeCommands();

	// retrieves the image in the session after scanning by file path. If the images does not exist-> nullptr
	// paths are not unique, possible optimization-> images can have an id
	Image* getImageByPath(const std::string& imgPath);

private:
	static unsigned ID;
	unsigned id;
	bool isActive;
	std::vector<Image*> images;
	std::vector<ImageCommand*> commands;		
	int lastCommandIndex;
};
