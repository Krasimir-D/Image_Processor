#pragma once
#include "ImageCommand.h"


// base class required for realizing an abstract commands factory
class ImageCommandCreator
{
public:
	ImageCommandCreator(const std::string& name); // Defines the type of ImageCommand that will be created based on the console input
	virtual ~ImageCommandCreator() = default;
	virtual ImageCommandCreator* clone() const = 0;

	// Checks whether the ImageCommand at input matches the current ImageCommand type
	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const;

	virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const = 0;

protected:
	const std::string name;
};

class CropCreator : public ImageCommandCreator
{
public:
	CropCreator() : ImageCommandCreator("crop") {}
	virtual ImageCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const override;
};


class MonochromeCreator : public ImageCommandCreator
{
public:
	MonochromeCreator() : ImageCommandCreator("monochrome") {}
	virtual ImageCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	 virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class NegativeCreator : public ImageCommandCreator
{
public:
	NegativeCreator() : ImageCommandCreator("negative") {}
	virtual ImageCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	 virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class GrayscaleCreator : public ImageCommandCreator
{
public:
	GrayscaleCreator() : ImageCommandCreator("grayscale") {}
	virtual ImageCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	 virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class RotateLeftCreator : public ImageCommandCreator
{
public:
	RotateLeftCreator() : ImageCommandCreator("rotate left") {}
	virtual ImageCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	 virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class RotateRightCreator : public ImageCommandCreator
{
public:
	RotateRightCreator() : ImageCommandCreator("rotate right") {}
	virtual ImageCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	 virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class FlipTopCreator : public ImageCommandCreator
{
public:
	FlipTopCreator() : ImageCommandCreator("flip top") {}
	virtual ImageCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	 virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const override;
};

class FlipLeftCreator : public ImageCommandCreator
{
public:
	FlipLeftCreator() : ImageCommandCreator("flip left") {}
	virtual ImageCommandCreator* clone() const override;

	virtual bool isIdenticalCommand(const std::vector<std::string>& arguments) const override;
	 virtual ImageCommand* createCommand(const std::vector<std::string>& arguments) const override;
};


