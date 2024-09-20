#include "Session.h"
#include "ImageIOFactory.hpp"
unsigned Session::ID = 0;

Session::Session()
	: id(++ID), isActive(true), lastCommandIndex(-1)
{
	std::cout << "Session with ID: " << id << " started" << std::endl;
}

Session::Session(Session&& other) noexcept
	: id(other.id),
	isActive(other.isActive),
	images(std::move(other.images)),
	commands(std::move(other.commands)),
	lastCommandIndex(other.lastCommandIndex)
{
	// Reset the moved-from object
	other.id = 0;
	other.isActive = false;
	other.lastCommandIndex = -1;
}

Session& Session::operator=(Session&& other) noexcept
{
	if (this != &other)
	{
		id = other.id;
		isActive = other.isActive;
		images = std::move(other.images);
		commands = std::move(other.commands);
		lastCommandIndex = other.lastCommandIndex;

		// Reset the moved-from object
		other.id = 0;
		other.isActive = false;
		other.lastCommandIndex = -1;
	}
	return *this;
}

Session::~Session()
{
	clearCommands();
	clearImages();
}

void Session::clearImages()
{
	size_t imagesCount = images.size();
	for (size_t i = 0; i < imagesCount; i++)
	{
		delete images[i];
	}
}

void Session::handleCommand(ImageCommand* cmd)
{
	// if a new command is added after a "undo" command has been executed "redo" should be no longer available 
	if (lastCommandIndex + 1 < commands.size())
	{
		commands.erase(commands.begin() + static_cast<size_t>(lastCommandIndex + 1), commands.begin() + commands.size());
	}

	commands.push_back(cmd);
	lastCommandIndex = static_cast<int>(commands.size() - 1);
}

void Session::listSession() const
{
	std::cout << "> Session " << id << " ; Loaded images: ";
	for (size_t i = 0; i < images.size(); i++)
	{
		std::cout << images[i]->getPath() << " ";
	}
	std::cout << std::endl;
}

void Session::executeCommands()
{
	if (lastCommandIndex < 0)
		return;

	size_t imagesCount = images.size();
	for (size_t i = 0; i <= lastCommandIndex; i++)
	{
		ImageCommand& temp = *commands[i];
		for (size_t i = 0; i < imagesCount; i++)
		{
			temp(images[i]);
		}
	}
	
	clearCommands();
	lastCommandIndex = -1;
}

Image* Session::getImageByPath(const std::string& imgPath)
{
	size_t imagesCount = images.size();
	for (size_t i = 0; i < imagesCount; i++)
	{
		if (images[i]->getPath() == imgPath)
			return images[i];
	}

	return nullptr;
}

void Session::add(const std::string& path)
{
	Image* img = ImageIOFactory::getFactory().load(path.c_str());
	executeCommands();
	images.push_back(img);
}

void Session::save()
{
	executeCommands();
	// set the default file names filename<time_of_modification>.extension
	size_t imagesCount = images.size();
	for (size_t i = 0; i < imagesCount; i++)
	{
		images[i]->setPath(CommandLine::timestampFilePath(images[i]->getPath()));
		ImageIOFactory::getFactory().save(*images[i]);
	}

	//images.clear();
	//isActive = false;
}

void Session::saveas(const std::vector<std::string>& paths)
{
	size_t pathsCount = paths.size();
	if (pathsCount > images.size())
	{
		throw std::invalid_argument("The count of the provided paths should be <= than the count of the images!");
	}

	executeCommands();
	for (size_t i = 0; i < pathsCount; i++)
	{
		images[i]->setPath(paths[i]);
		ImageIOFactory::getFactory().save(*images[i]);
	}
	for (size_t i = pathsCount; i < images.size(); i++)
	{
		images[i]->setPath(CommandLine::timestampFilePath(images[i]->getPath()));
		ImageIOFactory::getFactory().save(*images[i]);
	}

	//images.clear();
	//isActive = false;
}

void Session::undo()
{
	if (lastCommandIndex > -1)
	{
		lastCommandIndex--;
	}
	else
		std::cout << "No commands to undo yet!" << std::endl;
}

void Session::redo()
{
	if (lastCommandIndex + 1 < commands.size())
	{
		lastCommandIndex++;
	}
	else
		std::cout << "No commands to redo yet" << std::endl;
}

void Session::listSession()
{
	std::cout << "Session No. " << id << " Images in session:" << std::endl;
	for (size_t i = 0; i < images.size(); i++)
	{
		std::cout << images[i]->getPath() << std::endl;
	}
}

void Session::makeCollage(const std::string& path1, const std::string& path2, bool orientation)
{
	// apply previous commands so the collage is up to sinc
	executeCommands();
	// first we scan for the images in the session by their paths.
	// if they don't exist in the session-> cerr
	Image* img1 = getImageByPath(path1);
	if (!img1)
	{
		std::cerr << "Image with path: " << path1 << " is not in the session!\n";
		return;
	}

	Image* img2 = getImageByPath(path2);
	if (!img2)
	{
		std::cerr << "Image with path: " << path2 << " is not in the session!\n";
		return;
	}

	if (img1->getType() != img2->getType())
	{
		std::cerr << "Cannot make a collage from different types " << img1->getPath() << " " << img2->getPath() << std::endl;
		return;
	}

	std::string collagePath = CommandLine::removeFileExtension(img1->getPath()) + '_' + CommandLine::removeFileExtension(img2->getPath())
		+ '.' + CommandLine::extractFileExtension(img1->getPath());
	Image* collage;
	if (!orientation)
		collage = Image::verticalCollage(img1, img2);
	else
		collage = Image::horizontalCollage(img1, img2);

	collage->setPath(collagePath);
	ImageIOFactory::getFactory().save(*collage);
	delete collage;
}

void Session::setIsActive(bool val)
{
	isActive = val;
}

bool Session::getIsActive() const
{
	return isActive;
}

bool Session::getHasUsavedProgress() const
{
	return (lastCommandIndex > -1);
}

void Session::print() const
{
	std::cout << "Session: " << id << std::endl;
}

void Session::clearCommands()
{
	size_t commandCount = commands.size();
	for (size_t i = 0; i < commandCount; i++)
	{
		delete commands[i];
	}
	commands.clear();
}

void Session::displayUnsavedProgressDialog()
{
	std::cout << "> You have unsaved progress in ";
	print();
	std::cout << "> Save it now (y/n)? " << std::endl;

	std::string answer;
	std::getline(std::cin, answer);

	while (answer.size() != 1 || answer != "y" && answer != "n")
	{
		std::cout << "Unrecognized response! The only valid responses are: y/n. Enter a new response!" << std::endl;
		std::getline(std::cin, answer);
	}

	if (answer == "y")
	{
		save();
	}
	if (answer == "n")
	{
		// the commands and the images get cleared and all the progress remains unsaved
		clearCommands();
		clearImages();
	}

	isActive = false;
}