#pragma once
#include "ImageExporter.h"

class BmpExporter : public ImageExporter
{
public:
	virtual void saveImage(const char* path, const Image& image) const;
	virtual ImageExporter* clone() const override;
	virtual bool isFormatSupported(const char* magicNumber) const override;

protected:
	static constexpr char MAGIC_NUMBER_BMP[] = "BM";
};

