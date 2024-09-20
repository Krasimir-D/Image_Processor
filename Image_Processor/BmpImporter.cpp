#include "BmpImporter.h"
#include "ConverterUtils.h"
#include "BmpStructure.h"
#include "ImageIOFactory.hpp"
using namespace ConverterUtils;

Image* BmpImporter::loadImage(const char* path, const char* magicNumber) const
{    
    std::ifstream in(path, std::ios::binary);

    BmpFileHeader file_header;
    BmpInfoHeader info_header;
    std::vector<uint8_t> rawData;

    in.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    in.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (info_header.bit_count != 24)    
        throw std::runtime_error("The program only considers 24 bit BMP images!");    
    
    if (info_header.size < 0)
        throw std::runtime_error("The program can only treat BMP images with the origin in the bottom-left corner!");

    // jump to the pixel data location
    in.seekg(file_header.offset_data, in.beg);

    // adjust the header fields for output.
    // some editors will put extra info in  the image file, we only save the headers and the data
    file_header.offset_data = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader);
    info_header.size = sizeof(BmpInfoHeader);
    
    file_header.file_size = file_header.offset_data;

    // Here we check if we need to take into account row padding
    if (info_header.width % 4 == 0)
    {
        in.read(reinterpret_cast<char*>(rawData.data()), rawData.size());
        file_header.file_size += static_cast<uint32_t>(rawData.size());
    }

    unsigned rowStride = info_header.width * sizeof(Pixel) + Image::getRGBPixelPadding(info_header.width);
    rawData.resize(rowStride * info_header.height);
    in.read(reinterpret_cast<char*>(rawData.data()), rawData.size());

    std::vector<Pixel> aggregatedData = convertBmpToRgb(rawData, info_header.width, info_header.height);

    in.close();
    return new Image(ImageType::BMP, MAGIC_NUMBER_BMP, info_header.width, info_header.height, 0, aggregatedData);
}

bool BmpImporter::isFormatSupported(const char* magicNumber) const
{
    if(strcmp(magicNumber, MAGIC_NUMBER_BMP) != 0)
        return false;

    return true;
}

ImageImporter* BmpImporter::clone() const
{
    return new BmpImporter(*this);
}

static BmpImporter __;