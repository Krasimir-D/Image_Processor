#pragma once
#include "Image.h"

class ImageExporter
{
public:
	ImageExporter();
	virtual void saveImage(const char* path, const Image& image) const = 0;
	virtual ImageExporter* clone() const = 0;
	virtual ~ImageExporter() = default;	

	virtual bool isFormatSupported(const char* magicNumber) const = 0;
};

