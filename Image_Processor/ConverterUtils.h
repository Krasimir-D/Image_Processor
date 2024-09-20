#pragma once
#include "Image.h"
#include <vector>

namespace ConverterUtils
{
	// converts from RGB to bit per pixel format
	std::vector<uint8_t> convertToBitPixel(const std::vector<Pixel>& rgbData, size_t width, size_t height);

	// converts from bit per pixel to RGB
	std::vector<Pixel> convertBitToRGB(const std::vector<uint8_t>& rawData, size_t width, size_t height);

	// converts from pgm to RGB
	std::vector<Pixel> convertPgmToRGB(const std::vector<uint8_t>& rawData, size_t width, size_t height);
	std::vector<uint8_t> convertRgbToPgm(const std::vector<Pixel>& rawData, size_t width, size_t height);

	// converts from BGR to RGB and trims the padding
	std::vector<Pixel> convertBgrToRGB(const std::vector<Pixel>& rawData, size_t width, size_t height);
	// converts from RGB to BGR and adds neccessary padding
	std::vector<Pixel> convertRgbToBgr(const std::vector<Pixel>& rawData, size_t width, size_t height);

	// converts from bmp data to image.h style data	
	std::vector<Pixel> convertBmpToRgb(const std::vector<uint8_t>& rawData, size_t width, size_t height);
	std::vector<uint8_t> convertRgbToBmp(const std::vector<Pixel>& rawData, size_t width, size_t height);
}

