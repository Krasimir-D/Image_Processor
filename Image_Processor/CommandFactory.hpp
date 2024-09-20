#pragma once
#include "HeterogenicArray.hpp"
#include "ImageCommandCreators.h"
#include "SystemCommandCreators.h"

class CommandFactory
{
public:
	static CommandFactory& getFactory()
	{
		static CommandFactory theFactory;
		return theFactory;
	}

	// registers abstract class factory
	void registerImageCommand(const ImageCommandCreator* creator)
	{
		imageCommandCreators.push_back(creator);
	}

	void registerSystemCommand(const SystemCommandCreator* creator)
	{
		systemCommandCreators.push_back(creator);
	}

	ImageCommand* createImageCommand(const std::vector<std::string>& arguments)
	{
		const ImageCommandCreator* creator = getImageCommandCreator(arguments);
		if (!creator)
		{			
			return nullptr;
		}

		return creator->createCommand(arguments);
	}

	SystemCommand* createSystemCommand(const std::vector<std::string>& arguments)
	{
		const SystemCommandCreator* creator = getSystemCreator(arguments);
		if (!creator)
		{			
			return nullptr;
		}
		return creator->createCommand(arguments);
	}

private:
	const ImageCommandCreator* getImageCommandCreator(const std::vector<std::string>& arguments)
	{
		for (size_t i = 0; i < imageCommandCreators.size(); i++)
		{
			if (imageCommandCreators[i]->isIdenticalCommand(arguments))
				return imageCommandCreators[i];
		}

		return nullptr;
	}

	const SystemCommandCreator* getSystemCreator(const std::vector<std::string>& arguments)
	{
		for (size_t i = 0; i < systemCommandCreators.size(); i++)
		{
			if (systemCommandCreators[i]->isIdenticalCommand(arguments))
				return systemCommandCreators[i];
		}

		return nullptr;
	}

private:
	CommandFactory() = default;	
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory& other) = delete;

private:
	std::vector<const ImageCommandCreator*> imageCommandCreators;
	std::vector<const SystemCommandCreator*> systemCommandCreators;
};


