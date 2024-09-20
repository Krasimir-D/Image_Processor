#include "KkdExporter.h"
#include <fstream>
#include <cstring>
#include <iostream>

void KkdExporter::saveImage(const char* path, const Image& image) const
{
	std::ofstream out(path);
	if (!out)
		throw std::runtime_error("Unable to open file for writing!");

	out << MAGIC_NUMBER << '\n';
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

ImageExporter* KkdExporter::clone() const
{
    return new KkdExporter(*this);
}

bool KkdExporter::isFormatSupported(const char* magicNumber) const
{
    return strcmp(magicNumber, MAGIC_NUMBER) == 0;
}

static KkdExporter __;