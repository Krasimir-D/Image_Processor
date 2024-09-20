#include "KkdImporter.h"

// reading it like a ppm file
Image* KkdImporter::loadImage(const char* path, const char* magicNumber) const
{
    std::ifstream in(path);
    if (!in)
        throw "Unable to open for reading";

    in.ignore(2, '\n');
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

    return new Image(ImageType::KD, MAGIC_NUMBER, width, height, maxVal, data);
}

bool KkdImporter::isFormatSupported(const char* magicNumber) const
{
    return strcmp(magicNumber, MAGIC_NUMBER) == 0;
}

ImageImporter* KkdImporter::clone() const
{
    return new KkdImporter(*this);
}

// register
static KkdImporter __;
