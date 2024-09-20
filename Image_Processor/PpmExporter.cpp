#include "PpmExporter.h"
#include <fstream>
#include <cstring>
#include <iostream>

void PpmExporter::saveImage(const char* path, const Image& image) const
{
	if (strcmp(image.getMagicNumber(), MAGIC_NUMER_ASCII) == 0)
		saveAscii(path, image);
	else
		saveBinary(path, image);
}

ImageExporter* PpmExporter::clone() const
{
	return new PpmExporter(*this);
}

bool PpmExporter::isFormatSupported(const char* magicNumber) const
{
	return strcmp(magicNumber, MAGIC_NUMER_ASCII) == 0|| strcmp(magicNumber, MAGIC_NUMER_BINARY) == 0;
}

void PpmExporter::saveBinary(const char* path, const Image& image) const
{
	std::ofstream out(path, std::ios::binary);
	if (!out)
		throw std::runtime_error("Unable to open file for writing!");

	out << image.getMagicNumber() << '\n';
	out << image.getWidth() << " " << image.getHeight() << '\n';
	out << image.getMaxValuePerPixel() << '\n';

	std::vector<Pixel> data = image.getData();

	out.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(Pixel));

	out.close();
}

void PpmExporter::saveAscii(const char* path, const Image& image) const
{
	std::ofstream out(path);
	if (!out)
		throw std::runtime_error("Unable to open file for writing!");

	out << MAGIC_NUMER_ASCII << '\n';
	out << image.getWidth() << ' ' << image.getHeight() << std::endl;
	out << image.getMaxValuePerPixel() << std::endl;

	size_t index = 0;
	size_t width = image.getWidth();
	size_t height = image.getHeight();
	std::vector<Pixel> data = image.getData();

	std::string currentPixel = "";
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			index = y * width + x;
			currentPixel = std::to_string(data[index].red) + ' ' + std::to_string(data[index].green) + ' ' + std::to_string(data[index].blue) + "  ";
			out << currentPixel;
		}

		out << std::endl;
	}


	out.close();
}

static PpmExporter __;