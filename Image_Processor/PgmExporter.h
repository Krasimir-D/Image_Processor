#pragma once
#include "ImageExporter.h"

class PgmExporter : public ImageExporter
{
public:
	virtual void saveImage(const char* path, const Image& image) const override;
	virtual ImageExporter* clone() const override;
	virtual bool isFormatSupported(const char* magicNumber) const override;

protected:
	void saveBinary(const char* path, const Image& image) const;
	void saveAscii(const char* path, const Image& image) const;

protected:
	static constexpr char MAGIC_NUMBER_ASCII[] = "P2";
	static constexpr char MAGIC_NUMBER_BINARY[] = "P5";
};

