#include "Pixel.h"

const Pixel Pixel::WHITE_PIXEL = Pixel(255, 255, 255);
const Pixel Pixel::BLACK_PIXEL = Pixel(0, 0, 0);
const Pixel Pixel::PADDING_PIXEL = Pixel(69, 69, 69);


uint8_t Pixel::getLuminance() const
{
    constexpr float RED_COEFF = 0.21f;
    constexpr float GREEN_COEFF = 0.72f;
    constexpr float BLUE_COEFF = 0.07f;

    uint8_t luminance = RED_COEFF * red + GREEN_COEFF * green + BLUE_COEFF * blue;

    return luminance;
}

Pixel Pixel::getCompliment() const
{
    constexpr uint8_t MAX_VAL = 255;
    return Pixel(MAX_VAL-this->red, MAX_VAL-this->green, MAX_VAL-this->blue);
}

bool Pixel::operator==(const Pixel& other) const
{
    return (red == other.red) && (green == other.green) && (blue == other.blue);
}

std::ostream& operator<<(std::ostream& out, const Pixel& pixel)
{
    out << '(' << static_cast<unsigned>(pixel.red) << "," << static_cast<unsigned>(pixel.green) << ',' << static_cast<unsigned>(pixel.blue) << ')';
    return out;
}
