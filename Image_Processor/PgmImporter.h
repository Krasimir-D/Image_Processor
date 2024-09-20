#pragma once
#include "ImageImporter.h"

class PgmImporter : public ImageImporter
{
public:
	virtual Image* loadImage(const char* path, const char* magicNumber = nullptr) const override;
	virtual bool isFormatSupported(const char* magicNumber) const override;

	virtual ImageImporter* clone() const override;

protected:
	Image* loadAscii(std::ifstream& in) const;
	Image* loadBinary(std::ifstream& in) const;

protected:
	static constexpr char MAGIC_NUMBER_ASCII[] = "P2";
	static constexpr char MAGIC_NUMBER_BINARY[] = "P5";
};

