#pragma once
#include "ImageImporter.h"

class PpmImporter : public ImageImporter
{
public:
	virtual Image* loadImage(const char* path, const char* magicNumber) const override;
	virtual bool isFormatSupported(const char* magicNumber) const override;

	virtual ImageImporter* clone() const override;

protected:
	Image* loadAscii(std::ifstream& in) const;
	Image* loadBinary(std::ifstream& in) const;

private:
	static constexpr char MAGIC_NUMBER_ASCII[] = "P3";
	static constexpr char MAGIC_NUMBER_BINARY[] = "P6";

};

