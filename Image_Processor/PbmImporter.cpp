#include "PbmImporter.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "ConverterUtils.h"
using namespace ConverterUtils;
 
Image* PbmImporter::loadImage(const char* path, const char* magicNumber) const
{
	Image* img = nullptr;
	if (strcmp(magicNumber, MAGIC_NUMBER_ASCII) == 0)
	{
		std::ifstream in(path);
		// ignores the magic number
		in.ignore(2, '\n');
		img = loadAscii(in);
		in.close();
	}
	else
	{
		std::ifstream in(path, std::ios::binary);
		// ignores the magic number
		in.ignore(2, '\n');
		img = loadBinary(in);
		in.close();
	}
	img->setPath(path);
	return img;
}

bool PbmImporter::isFormatSupported(const char* magicNumber) const
{
	if (strcmp(magicNumber, MAGIC_NUMBER_ASCII) == 0)
		return true;

	if (strcmp(magicNumber, MAGIC_NUMBER_BINARY) == 0)
		return true;

	return false;
}

ImageImporter* PbmImporter::clone() const
{
	return new PbmImporter(*this);
}

Image* PbmImporter::loadBinary(std::ifstream& in) const
{
	unsigned width = 0;
	unsigned height = 0;
	in >> width;
	in >> height;
	unsigned rowStride = (width + 7) / 8;
	std::vector<uint8_t> rawData(height * rowStride);
	in.ignore(1, '\n');
	in.read(reinterpret_cast<char*>(rawData.data()), rawData.size());
	std::vector<Pixel> aggregatedData = convertBitToRGB(rawData, width, height);

	return new Image(ImageType::PBM, MAGIC_NUMBER_BINARY, width, height, 1, aggregatedData);
}

Image* PbmImporter::loadAscii(std::ifstream& in) const
{
	unsigned width, height;

	size_t pos = in.tellg();
	char currentSymbol;
	in >> currentSymbol;
	// handles possible consecutive comment lines starting with '#'
	while (currentSymbol == '#')
	{
		in.ignore(1024, '\n');
		pos = in.tellg();
		in >> currentSymbol;
	}
	in.seekg(pos, std::ios::beg);
	in >> width;
	in >> height;

	std::vector<Pixel> data;
	data.reserve(width * height);
	
	unsigned currentPixel = 0;
	while (!in.eof())
	{
		in >> currentPixel;
		if (currentPixel != 0 && currentPixel != 1)
			throw std::runtime_error("Unrecognized format!");

		(currentPixel == 0) ? data.push_back(Pixel::BLACK_PIXEL) : data.push_back(Pixel::WHITE_PIXEL);
	}

	return new Image(ImageType::PBM, MAGIC_NUMBER_ASCII, width, height, 1, data);
}

static PbmImporter __;