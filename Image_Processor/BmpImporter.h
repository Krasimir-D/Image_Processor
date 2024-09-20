#pragma once
#include "ImageImporter.h"

class BmpImporter : public ImageImporter
{
public:
	virtual Image* loadImage(const char* path, const char* magicNumber = nullptr) const override;
	virtual bool isFormatSupported(const char* magicNumber) const override;

	virtual ImageImporter* clone() const override;

private:
	static constexpr char MAGIC_NUMBER_BMP[] = "BM";
	
};

