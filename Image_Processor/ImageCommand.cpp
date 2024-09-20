#include "ImageCommand.h"
#include "ImageIOFactory.hpp"

Crop::Crop(unsigned top_left_x, unsigned top_left_y, unsigned bottom_right_x, unsigned bottom_right_y)
	: ImageCommand("crop")
{
	if (top_left_x > bottom_right_x || top_left_y > bottom_right_y)
	{
		std::cerr << "Invalid arguments for cropping!\n";
		throw std::invalid_argument("Invalid arguments for <crop>!");
	}

	this->top_left_x = top_left_x;
	this->top_left_y = top_left_y;
	this->bottom_right_x = bottom_right_x;
	this->bottom_right_y = bottom_right_y;
}

ImageCommand* Crop::clone() const
{
	return new Crop(*this);
}

unsigned Crop::get_top_left_x() const
{
	return top_left_x;
}

unsigned Crop::get_top_left_y() const
{
	return top_left_y;
}

unsigned Crop::get_bottom_right_x() const
{
	return bottom_right_x;
}

unsigned Crop::get_bottom_right_y() const
{
	return bottom_right_y;
}

void Crop::execute(Image* img) const
{
	img->crop(top_left_x, top_left_y, bottom_right_x, bottom_right_y);
}

Monochrome::Monochrome()
	: ImageCommand("monochrome")
{
}

ImageCommand* Monochrome::clone() const
{
	return new Monochrome(*this);
}

void Monochrome::execute(Image* img) const
{
	img->monochrome();
}

Negative::Negative()
	: ImageCommand("negative")
{
}

ImageCommand* Negative::clone() const
{
	return new Negative(*this);
}

void Negative::execute(Image* img) const
{
	img->negative();
}

Grayscale::Grayscale()
	: ImageCommand("grayscale")
{
}

ImageCommand* Grayscale::clone() const
{
	return new Grayscale(*this);
}

void Grayscale::execute(Image* img) const
{
	img->grayscale();
}

RotateLeft::RotateLeft()
	: ImageCommand("rotate left")
{
}

ImageCommand* RotateLeft::clone() const
{
	return new RotateLeft(*this);
}

void RotateLeft::execute(Image* img) const
{
	img->rotateLeft();
}


RotateRight::RotateRight()
	: ImageCommand("rotate right")
{
}

ImageCommand* RotateRight::clone() const
{
	return new RotateRight(*this);
}

void RotateRight::execute(Image* img) const
{
	img->rotateRight();
}

FlipTop::FlipTop()
	: ImageCommand("flip top")
{
}

ImageCommand* FlipTop::clone() const
{
	return new FlipTop(*this);
}

void FlipTop::execute(Image* img) const
{
	img->flipTop();
}

FlipLeft::FlipLeft()
	: ImageCommand("flip left")
{
}

ImageCommand* FlipLeft::clone() const
{
	return new FlipLeft(*this);
}

void FlipLeft::execute(Image* img) const
{
	img->flipLeft();
}

ImageCommand::ImageCommand(const std::string& name)
	: name(name)
{
}

void ImageCommand::operator()(Image* img)
{
	execute(img);
}

const std::string& ImageCommand::getName() const
{
	return name;
}

