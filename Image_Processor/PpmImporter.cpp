#include "PpmImporter.h"
#include <iostream>
#include <cstring>

Image* PpmImporter::loadImage(const char* path, const char* magicNumber) const
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

bool PpmImporter::isFormatSupported(const char* magicNumber) const
{
    if (strcmp(magicNumber, MAGIC_NUMBER_ASCII) == 0)
        return true;
    if (strcmp(magicNumber, MAGIC_NUMBER_BINARY) == 0)
        return true;

    return false;
}

ImageImporter* PpmImporter::clone() const
{
    return new PpmImporter(*this);
}

Image* PpmImporter::loadAscii(std::ifstream& in) const
{
    unsigned width, height, maxVal;

    unsigned pos = static_cast<unsigned>(in.tellg());
    char current;
    in >> current;
    // handles possible consecutive comment lines starting with '#'
    while (current == '#')
    {
        in.ignore(1024, '\n');
        pos = in.tellg();
        in >> current;
    }
    in.seekg(pos, std::ios::beg);
    in >> width >> height >> maxVal;
    std::vector<Pixel> data;
    data.reserve(width * height);

    unsigned red, green, blue;
    while (!in.eof())
    { 
        in >> red >> green >> blue;
        data.push_back(Pixel(red, green, blue));
    }

    return new Image(ImageType::PPM, MAGIC_NUMBER_ASCII, width, height, maxVal, data);
}

Image* PpmImporter::loadBinary(std::ifstream& in) const
{
    unsigned width, height, maxVal;

    in >> width >> height >> maxVal;

    if (maxVal > 255)
        throw std::runtime_error("Unrecognized format!");

    std::vector<Pixel> data(width * height);
    in.ignore(1, '\n');

    in.read(reinterpret_cast<char*>(data.data()), data.size() * sizeof(Pixel));

    return new Image(ImageType::PPM, MAGIC_NUMBER_BINARY, width, height, maxVal, data);
}

static PpmImporter __;