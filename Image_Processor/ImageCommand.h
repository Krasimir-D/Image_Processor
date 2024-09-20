#pragma once
#include "Image.h"
#include "CommandLine.h"

// base class for commands
class ImageCommand
{
public:
	ImageCommand(const std::string& name);

	virtual ImageCommand* clone() const = 0;
	virtual ~ImageCommand() = default;
	void operator()(Image* img = nullptr);
	const std::string& getName() const;
		
protected:
	const std::string name;

private:
	virtual void execute(Image* img = nullptr) const = 0;
};

class Crop : public ImageCommand
{
public:
	Crop(unsigned top_left_x, unsigned top_left_y, unsigned bottom_right_x, unsigned bottom_right_y);

	virtual ImageCommand* clone() const override;

	unsigned get_top_left_x() const;
	unsigned get_top_left_y() const;
	unsigned get_bottom_right_x() const;
	unsigned get_bottom_right_y() const;

private:
	virtual void execute(Image* img) const override;

private:
	unsigned top_left_x;
	unsigned top_left_y;
	unsigned bottom_right_x;
	unsigned bottom_right_y;
};

class Monochrome : public ImageCommand
{
public:
	Monochrome();
	virtual ImageCommand* clone() const override;

private:
	virtual void execute(Image* img) const override;
};

class Negative : public ImageCommand
{
public:
	Negative();
	virtual ImageCommand* clone() const override;

private:
	virtual void execute(Image* img) const override;
};

class Grayscale : public ImageCommand
{
public:
	Grayscale();
	virtual ImageCommand* clone() const override;

private:
	virtual void execute(Image* img) const override;
};

class RotateLeft : public ImageCommand
{
public:
	RotateLeft();
	virtual ImageCommand* clone() const override;

private:
	virtual void execute(Image* img) const override;
};

class RotateRight : public ImageCommand
{
public:
	RotateRight();
	virtual ImageCommand* clone() const override;

private:
	virtual void execute(Image* img) const override;
};

class FlipTop : public ImageCommand
{
public:
	FlipTop();
	virtual ImageCommand* clone() const override;

private:
	virtual void execute(Image* img) const override;
};

class FlipLeft : public ImageCommand
{
public:
	FlipLeft();
	virtual ImageCommand* clone() const override;

private:
	virtual void execute(Image* img) const override;
};




