#pragma once
#include "Image.h"
#include <fstream>

class ImageImporter
{
public:
	ImageImporter();
	virtual Image* loadImage(const char* path, const char* magicNumber = nullptr) const = 0;
	virtual bool isFormatSupported(const char* magicNumber) const = 0;

	virtual ImageImporter* clone() const = 0;

	virtual ~ImageImporter() = default;

protected:
	static constexpr unsigned MAGIC_NUMBER_LEN = 2;
};



