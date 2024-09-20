#include "PbmExporter.h"
#include <fstream>
#include <cstring>
#include "ConverterUtils.h"
using namespace ConverterUtils;

void PbmExporter::saveImage(const char* path, const Image& image) const
{
	if (strcmp(image.getMagicNumber(), MAGIC_NUMBER_ASCII) == 0)
		saveAscii(path, image);
	else
		saveBinary(path, image);
}

ImageExporter* PbmExporter::clone() const
{
	return new PbmExporter(*this);
}

bool PbmExporter::isFormatSupported(const char* magicNumber) const
{
	return strcmp(magicNumber, MAGIC_NUMBER_ASCII) == 0 || strcmp(magicNumber, MAGIC_NUMBER_BINARY) == 0;
}

void PbmExporter::saveBinary(const char* path, const Image& image) const
{
	std::ofstream out(path, std::ios::binary);
	if (!out)
		throw std::runtime_error("Could not open for writing!");
	out << image.getMagicNumber() << std::endl;
	out << image.getWidth() << " " << image.getHeight() << std::endl;

	std::vector<uint8_t> aggregatedData = convertToBitPixel(image.getData(), image.getWidth(), image.getHeight());
	out.write(reinterpret_cast<const char*>(aggregatedData.data()), aggregatedData.size());

	out.close();
}

void PbmExporter::saveAscii(const char* path, const Image& image) const
{
	std::ofstream out(path);
	if (!out)
		throw std::runtime_error("Could not open file for writing!");

	unsigned width = image.getWidth();
	unsigned height = image.getHeight();
	std::vector<Pixel> data = image.getData();

	out << image.getMagicNumber() << std::endl;
	out << image.getWidth() << ' ' << image.getHeight() << std::endl;

	unsigned index = 0;
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			index = y * width + x;
			out << ((data[index] == Pixel::BLACK_PIXEL) ? 1 : 0 ) << ' ';
		}
		
		out << std::endl;
	}

	out.close();
}

static PbmExporter __;




