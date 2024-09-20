#include "ConverterUtils.h"

std::vector<uint8_t> ConverterUtils::convertToBitPixel(const std::vector<Pixel>& rgbData, size_t width, size_t height)
{
	size_t padding = Image::getRGBPixelPadding(width);
	size_t iter = 0;
	size_t index = 0;

	size_t bytesPerRow = (width + 7) / 8; // Calculate the number of bytes per row
	std::vector<uint8_t> result(height * bytesPerRow, 0); // Initialize result with zeros

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			index = y * padding + iter++;
			if (index == rgbData.size())
				return result;

			Pixel temp = rgbData[index];
			if (temp == Pixel::BLACK_PIXEL)
			{
				result[y * bytesPerRow + x / 8] |= (128 >> (x % 8));
			}
		}
	}

	return result;
}

std::vector<Pixel> ConverterUtils::convertBitToRGB(const std::vector<uint8_t>& rawData, size_t width, size_t height)
{
	std::vector<Pixel> result;
	size_t bytesPerRow = (width + 7) / 8;
	size_t padCount = Image::getRGBPixelPadding(width);

	size_t mask = 128;

	uint8_t currentByte = 0;
	uint8_t curentBit = 0;
	unsigned bitIndex = 0;
	for (size_t i = 0; i < height * bytesPerRow; i++)
	{
		currentByte = rawData[i];
		bitIndex = 0;
		size_t traverse = 0;
		while (bitIndex < width && traverse < 8)
		{
			curentBit = currentByte & (mask >> traverse);
			if (curentBit)
				result.push_back(Pixel::BLACK_PIXEL);

			else
				result.push_back(Pixel::WHITE_PIXEL);

			bitIndex++;
			traverse++;			
		}
	}

	return result;
}

std::vector<Pixel> ConverterUtils::convertPgmToRGB(const std::vector<uint8_t>& rawData, size_t width, size_t height)
{
	std::vector<Pixel> result;
	result.reserve(width * height);

	uint8_t temp = 0;
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			temp = rawData[i * width + j];
			result.push_back(Pixel(temp, temp, temp));
		}
	}

	return result;
}

std::vector<uint8_t> ConverterUtils::convertRgbToPgm(const std::vector<Pixel>& rawData, size_t width, size_t height)
{
	std::vector<uint8_t> result;
	
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			size_t index = i * width + j;
			result.push_back((rawData[index].red));
		}
	}

	return result;
}

std::vector<Pixel> ConverterUtils::convertBgrToRGB(const std::vector<Pixel>& rawData, size_t width, size_t height)
{
	size_t padding = Image::getRGBPixelPadding(width);

	std::vector<Pixel> result;
	result.reserve(width * height);

	size_t rowStride = width + padding; // Calculate the number of bytes per row
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			Pixel temp = rawData[y * rowStride + x];
			std::swap(temp.red, temp.blue);
			result.push_back(temp);
		}
	}
	
	return result;
}

std::vector<Pixel> ConverterUtils::convertRgbToBgr(const std::vector<Pixel>& rawData, size_t width, size_t height)
{
	size_t padding = Image::getRGBPixelPadding(width);

	std::vector<Pixel> result;
	result.reserve((width + padding) * height);	

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			Pixel temp = rawData[y * width + x];
			std::swap(temp.red, temp.blue);
			result.push_back(temp);
		}				
	}

	return result;
}

std::vector<Pixel> ConverterUtils::convertBmpToRgb(const std::vector<uint8_t>& rawData, size_t width, size_t height)
{
	std::vector<Pixel> result;
	result.reserve(width * height);

	size_t rowStride = width * sizeof(Pixel) + Image::getRGBPixelPadding(width);
	width *= sizeof(Pixel);

	int index = 0;
	// reading from the bottom-left corner from left to right due to bmp specifications
	for (int y = height -1; y >= 0; y--)
	{
		for (int x = 0; x < width - 2; x+=3)
		{
			index = y * rowStride + x;
			result.push_back(Pixel(rawData[index + 2], rawData[index + 1], rawData[index]));
		}
	}

	return result;
}

std::vector<uint8_t> ConverterUtils::convertRgbToBmp(const std::vector<Pixel>& rawData, size_t width, size_t height)
{
	std::vector<uint8_t> result;
	size_t padding = Image::getRGBPixelPadding(width);
	int index = 0;

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			index = y * width + x;
			result.push_back(rawData[index].blue);
			result.push_back(rawData[index].green);
			result.push_back(rawData[index].red);;
		}

		for (size_t i = 0; i < padding; i++)
		{
			result.push_back(0);
		}
	}

	return result;
}

