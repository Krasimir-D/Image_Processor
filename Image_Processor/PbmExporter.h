#pragma 
#include "ImageExporter.h"

class PbmExporter : public ImageExporter
{
public:
	void saveImage(const char* path, const Image& image) const override;
	virtual ImageExporter* clone() const override;

	virtual bool isFormatSupported(const char* magicNumber) const override;

protected:
	void saveBinary(const char* path, const Image& image) const;
	void saveAscii(const char* path, const Image& image) const;

protected:
	static constexpr char MAGIC_NUMBER_ASCII[] = "P1";
	static constexpr char MAGIC_NUMBER_BINARY[] = "P4";
};

