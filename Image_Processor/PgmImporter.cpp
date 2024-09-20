#include "PgmImporter.h"
#include <iostream>
#include <cstring>
#include "ConverterUtils.h"


Image* PgmImporter::loadImage(const char* path, const char* magicNumber) const
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

bool PgmImporter::isFormatSupported(const char* magicNumber) const
{
	if (strcmp(MAGIC_NUMBER_ASCII, magicNumber) == 0)
		return true;
	if (strcmp(MAGIC_NUMBER_BINARY, magicNumber) == 0)
		return true;

	return false;
}

ImageImporter* PgmImporter::clone() const
{
	return new PgmImporter(*this);
}

Image* PgmImporter::loadAscii(std::ifstream& in) const
{
	unsigned width, height, maxVal = 0;
	size_t pos = static_cast<size_t>(in.tellg());
	char currentSymbol;

	in >> currentSymbol;
	while (currentSymbol == '#')
	{
		in.ignore(1024, '\n');
		pos = static_cast<size_t>(in.tellg());
		in >> currentSymbol;
	}

	in.seekg(pos, std::ios::beg);
	in >> width;
	in >> height;
	in >> maxVal;

	std::vector<Pixel> data;
	data.reserve(width * height);
	unsigned currentPixel = 0;

	while (!in.eof())
	{
		in >> currentPixel;
		data.push_back(Pixel(currentPixel, currentPixel, currentPixel));
	}

	return new Image(ImageType::PGM, MAGIC_NUMBER_ASCII, width, height, maxVal, data);
}

Image* PgmImporter::loadBinary(std::ifstream& in) const
{
	unsigned width = 0;
	unsigned height = 0;
	unsigned maxValuePerPixel = 0;

	in >> width;
	in >> height; 
	in >> maxValuePerPixel;
	if (maxValuePerPixel > 255)
		throw std::invalid_argument("Unrecognized format!");
	
	std::vector<uint8_t> rawData(width*height);
	in.ignore(1, '\n');
	in.read(reinterpret_cast<char*>(rawData.data()), rawData.size());
	std::vector<Pixel> aggregatedData = ConverterUtils::convertPgmToRGB(rawData, width, height);

	return new Image(ImageType::PGM, MAGIC_NUMBER_BINARY, width, height, maxValuePerPixel, aggregatedData);
}

static PgmImporter __;