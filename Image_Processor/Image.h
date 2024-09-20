#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Pixel.h"

enum class ImageType
{
	UNKNOWN = -1,
	PBM,
	PGM,
	PPM,
	BMP,
	KD
};

// identifies the pixel format
//struct PixelDesc
//{			
//	unsigned bitDepth;	// bits per channel (e.g. 8, 16, 24)
//	unsigned channelCount;   // number of channels
//	std::string channelOrder; // order of channels (e.g. "RGB", "BGR") or "Non" for format with less than 3 channels
//	unsigned rowAlignment;	// alignment or padding info for rows
//
//	PixelDesc(unsigned bitDepth, unsigned channelCount, const std::string& channelOrder, unsigned rowAlignment)
//		: bitDepth(bitDepth), channelCount(channelCount), channelOrder(channelOrder), rowAlignment(rowAlignment) {}
//};

// a wrap class, product of the importer's loadImage method
class Image
{
public:	
	Image(ImageType type, const char magicNumber[3], size_t width, size_t height, size_t maxValuePerPixel, const std::vector<Pixel>& data);
	
	ImageType getType() const;
	const char* getMagicNumber() const;
	size_t getWidth() const;
	size_t getHeight() const;
	size_t getMaxValuePerPixel() const;
	const std::vector<Pixel>& getData() const;
	
	static size_t getRGBPixelPadding(size_t width);

	void setType(ImageType ioObject);
	void setMaxValuePerPixel(size_t maxValuePerPixel);
	void setPath(const std::string& path);

	size_t getPadding() const;
	const std::string& getPath() const;

public:
	// commands
 	void grayscale();
	void monochrome();
	void negative();
	void rotateLeft(bool isRotating = false);
	void rotateRight(bool isRotating = false);
	void flipTop();
	void flipLeft();
	void crop(size_t top_left_x, size_t top_left_y, size_t bottom_right_x, size_t bottom_right_y);

public:
	// functions producing a collage from two images from the same file format
	static Image* horizontalCollage(const Image* img1, const Image* img2);
	static Image* verticalCollage(const Image* img1, const Image* img2);

private:
	std::string path;
	ImageType type;	

	char magicNumber[3];
	size_t width; 
	size_t height;
	size_t maxValuePerPixel; // field, which helps support PGM and PPM
	std::vector<Pixel> data; // vector of pixels in (RGB) format. uint8_t <-> 3 bytes
};

