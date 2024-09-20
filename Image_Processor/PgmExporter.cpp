#include "PgmExporter.h"
#include <cstring>
#include "ConverterUtils.h"
#include <fstream>

void PgmExporter::saveImage(const char* path, const Image& image) const
{
	if (strcmp(image.getMagicNumber(), MAGIC_NUMBER_ASCII) == 0)
		saveAscii(path, image);
	else
		saveBinary(path, image);
}

ImageExporter* PgmExporter::clone() const
{
	return new PgmExporter(*this);
}

bool PgmExporter::isFormatSupported(const char* magicNumber) const
{
	return strcmp(magicNumber, MAGIC_NUMBER_ASCII) == 0 || strcmp(magicNumber, MAGIC_NUMBER_BINARY) == 0;
}

void PgmExporter::saveBinary(const char* path, const Image& image) const
{
	std::ofstream out(path, std::ios::binary);
	if (!out)
		throw std::runtime_error("Could not open file for writing!");

	out << image.getMagicNumber() << std::endl;
	out << image.getWidth() << " " << image.getHeight() << std::endl;
	out << image.getMaxValuePerPixel() << std::endl;

	std::vector<uint8_t> aggregatedData = ConverterUtils::convertRgbToPgm(image.getData(), image.getWidth(), image.getHeight());
	out.write(reinterpret_cast<const char*>(aggregatedData.data()), aggregatedData.size());

	out.close();
}

void PgmExporter::saveAscii(const char* path, const Image& image) const
{
	std::ofstream out(path);
	if (!out)
		throw std::runtime_error("Unable to open file for writing!");

	size_t width = image.getWidth();
	size_t height = image.getHeight();
	std::vector<Pixel> data = image.getData();

	out << MAGIC_NUMBER_ASCII << std::endl;
	out << width << ' ' << height << std::endl;
	out << image.getMaxValuePerPixel() << std::endl;
	
	size_t index = 0;
	std::string pixel = "";
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			index = y * width + x;
			pixel = std::to_string(data[index].red) + ' ';
			out << pixel;
		}

		out << std::endl;
	}

	out.close();
}

static PgmExporter __;