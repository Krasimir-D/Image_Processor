#include "BmpExporter.h"
#include "BmpStructure.h"
#include "ConverterUtils.h"
#include <cstring>
#include <fstream>
using namespace ConverterUtils;


void BmpExporter::saveImage(const char* path, const Image& image) const
{
	std::ofstream out(path, std::ios::binary);
	if (!out)
		throw std::runtime_error("Unable to open file for writing!");

	BmpFileHeader file_header;
	BmpInfoHeader info_header;

	info_header.bit_count = 24;
	file_header.offset_data = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader);
	info_header.size = sizeof(BmpInfoHeader);

	info_header.width = image.getWidth();
	info_header.height = image.getHeight();
	
	std::vector<uint8_t> aggregatedData = convertRgbToBmp(image.getData(), image.getWidth(), image.getHeight());
	file_header.file_size = file_header.offset_data + static_cast<uint32_t>(aggregatedData.size());

	out.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
	out.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));
	out.write(reinterpret_cast<const char*>(aggregatedData.data()), aggregatedData.size());

	out.close();
}

ImageExporter* BmpExporter::clone() const
{
	return new BmpExporter(*this);
}

bool BmpExporter::isFormatSupported(const char* magicNumber) const
{
	return strcmp(magicNumber, MAGIC_NUMBER_BMP) == 0;
}

static BmpExporter __;