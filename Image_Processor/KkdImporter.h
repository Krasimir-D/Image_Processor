#pragma once
#include "ImageImporter.h"

class KkdImporter : public ImageImporter
{
public:
	virtual Image* loadImage(const char* path, const char* magicNumber = nullptr) const override;
	virtual bool isFormatSupported(const char* magicNumber) const override;

	virtual ImageImporter* clone() const override;

protected:
	static constexpr char MAGIC_NUMBER[] = "KD";
};

