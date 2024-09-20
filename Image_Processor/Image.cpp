#include "Image.h"
#include <cstring>
#pragma warning (disable : 4996)

Image::Image(ImageType type, const char magicNumber[3], size_t width, size_t height, size_t maxValuePerPixel, const std::vector<Pixel>& data)
	:path(""), type(type), magicNumber{}, width(width), height(height), maxValuePerPixel(0), data(data)
{
	strcpy(this->magicNumber, magicNumber);
	setMaxValuePerPixel(maxValuePerPixel);
}

ImageType Image::getType() const
{
	return type;
}

const char* Image::getMagicNumber() const
{
	return magicNumber;
}

size_t Image::getWidth() const
{
	return width;
}

size_t Image::getHeight() const
{
	return height;
}

size_t Image::getMaxValuePerPixel() const
{
	return maxValuePerPixel;
}

const std::vector<Pixel>& Image::getData() const
{
	return data;
}

void Image::setType(ImageType ioObject)
{
	this->type = ioObject;
}

void Image::setMaxValuePerPixel(size_t maxValuePerPixel)
{
	if (maxValuePerPixel > 255)
		throw std::invalid_argument("the max value per uint8_t can be 255!");

	this->maxValuePerPixel = maxValuePerPixel;
}


void Image::setPath(const std::string& path)
{
	this->path = path;
}

size_t Image::getRGBPixelPadding(size_t width)
{
	size_t rowStride = 3 * width;
	size_t padding = (4 - (rowStride % 4)) % 4;

	return padding;
}

const std::string& Image::getPath() const
{
	return path;
}

void Image::grayscale()
{
	// pbm's and pgm's do not need grayscaling. If a picture has a maxValuePerPixel of 1 it means it already is black and white
	if (type == ImageType::PBM || type == ImageType::PGM || maxValuePerPixel == 1)
		return;

	unsigned iter = 0;
	unsigned index = 0;

	size_t limit = data.size();

	for (size_t i = 0; i < limit; i++)
	{
		uint8_t grayLuminance = data[i].getLuminance();
		data[i].red = grayLuminance;
		data[i].green = grayLuminance;
		data[i].blue = grayLuminance;
	}
}

void Image::monochrome()
{
	if (type == ImageType::PBM)
		return;

	constexpr unsigned threshold = 128;

	size_t limit = data.size();

	for (size_t i = 0; i < limit; i++)
	{
		uint8_t grayLuminance = data[i].getLuminance();
		if (grayLuminance < threshold)
			data[i] = Pixel::BLACK_PIXEL;
		else
			data[i] = Pixel::WHITE_PIXEL;
	}

	maxValuePerPixel = 1;
}

void Image::negative()
{
	unsigned iter = 0;
	unsigned index = 0;

	size_t limit = data.size();
	for (size_t i = 0; i < limit; i++)
	{
		data[i] = data[i].getCompliment();
	}
}

void Image::rotateLeft(bool isRotating)
{
	// swap dimensions: if image is 2x3, result should be 3x2
	std::vector<Pixel> newData;
	newData.reserve(height * width);

	size_t index = 0;
	for (int x = static_cast<int>(width - 1); x >= 0; x--)
	{
		index = x;
		for (size_t y = 0; y < height; y++)
		{
			Pixel temp = data[index];
			newData.push_back(data[index]);
			index += width;
		}
	}

	data = std::move(newData);
	std::swap(width, height);
}

void Image::rotateRight(bool isRotating)
{	
	std::vector<Pixel> newData;
	newData.reserve(height * width);

	for (size_t x = 0; x < width; x++)
	{
		for (int y = static_cast<int>(height - 1); y >= 0; y--)
		{
			Pixel temp = data[y * width + x];
			newData.push_back(temp);
		}
	}

	data = std::move(newData);
	std::swap(width, height);
}

void Image::flipTop()
{
	std::vector<Pixel> newData;
	newData.reserve(height * width);

	for (int y = static_cast<int>(height - 1); y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			Pixel temp = data[y * width + x];
			newData.push_back(temp);
		}
	}

	data = std::move(newData);
}

void Image::flipLeft()
{
	std::vector<Pixel> newData;
	newData.reserve(height * width);

	for (size_t y = 0; y < height; y++)
	{
		for (int x = static_cast<int>(width - 1); x >= 0; x--)
		{
			Pixel temp = data[y * width + x];
			newData.push_back(temp);
		}
	}

	data = std::move(newData);
}

void Image::crop(size_t top_left_x, size_t top_left_y, size_t bottom_right_x, size_t bottom_right_y)
{

	// clock it back so it belongs in the image
	if (top_left_x > width)
		top_left_x = 0;

	if (top_left_y > height)
		top_left_y = 0;

	if (bottom_right_x > width)
		bottom_right_x = width;

	if (bottom_right_y > height)
		bottom_right_y = height;

	size_t newWidth = bottom_right_x - top_left_x;
	size_t newHeight = bottom_right_y - top_left_y;

	std::vector<Pixel> result;
	result.reserve(newWidth * newHeight);
	size_t index = 0;

	for (size_t y = top_left_y; y < newHeight; y++)
	{
		for (size_t x = top_left_x; x < newWidth; x++)
		{
			index = y * width + x;
			result.push_back(data[index]);
		}
	}

	data = result;
	width = newWidth;
	height = newHeight;
}

Image* Image::horizontalCollage(const Image* img1, const Image* img2)
{
	// Determine the new dimensions of the collage
	size_t newHeight = std::max(img1->height, img2->height);
	size_t newWidth = img1->width + img2->width;

	// Calculate the height difference between the two images
	size_t differenceHeight = std::abs(static_cast<int>(img1->height) - static_cast<int>(img2->height));

	// Initialize the collage pixel data
	std::vector<Pixel> collageData(newWidth * newHeight, Pixel::BLACK_PIXEL); // Initialize with black pixels

	// Determine which image is smaller and set the left and right images accordingly
	const Image* leftImage = (img1->height < img2->height) ? img1 : img2;
	const Image* rightImage = (img1->height < img2->height) ? img2 : img1;

	// Copy the left image data into the collage, padding the top with black pixels if necessary
	for (size_t x = 0; x < leftImage->width; ++x)
	{
		for (size_t y = 0; y < leftImage->height; ++y)
		{
			size_t index = y * leftImage->width + x;
			size_t indexCollage = (y + differenceHeight) * newWidth + x;
			collageData[indexCollage] = leftImage->data[index];
		}
	}

	// Copy the right image data into the collage, directly beside the left image
	for (size_t x = 0; x < rightImage->width; ++x)
	{
		for (size_t y = 0; y < rightImage->height; ++y)
		{
			size_t index = y * rightImage->width + x;
			size_t indexCollage = y * newWidth + x + leftImage->width;
			collageData[indexCollage] = rightImage->data[index];
		}
	}

	// Determine the new max value per pixel
	size_t newMaxValuePerPixel = std::max(img1->maxValuePerPixel, img2->maxValuePerPixel);

	// Create and return the new collage image
	return new Image(img1->type, img1->magicNumber, newWidth, newHeight, newMaxValuePerPixel, collageData);
}

Image* Image::verticalCollage(const Image* img1, const Image* img2)
{
	size_t newHeight = img1->height + img2->height;
	size_t newWidth = (img1->width > img2->width) ? img1->width : img2->width; // the new widht will be 

	size_t differenceWidth = (img1->width == newWidth) ? newWidth - img2->width : newWidth - img1->width;
	std::vector<Pixel> collageData;
	collageData.reserve(newHeight * newWidth);

	std::vector<Pixel> topImageData;
	std::vector<Pixel> bottomImageData;
	size_t topImageHeight;
	size_t topImageWidth;
	size_t bottomImageHeight;
	size_t bottomImageWidth;
	if (newWidth == img1->width)
	{
		topImageData = img2->getData();
		topImageHeight = img2->height;
		topImageWidth = img2->width;
		bottomImageData = img1->getData();
		bottomImageHeight = img1->height;
		bottomImageWidth = img1->width;
	}
	else
	{
		topImageData = img1->data;
		topImageHeight = img1->height;
		topImageWidth = img1->width;
		bottomImageData = img2->data;
		bottomImageHeight = img2->height;
		bottomImageWidth = img2->width;
	}

	size_t index = 0;
	// firstly, write the smaller one
	for (size_t y = 0; y < topImageHeight; y++)
	{
		for (size_t x = 0; x < topImageWidth; x++)
		{
			index = y * topImageWidth + x;
			collageData.push_back(topImageData[index]);
		}

		for (size_t i = 0; i < differenceWidth; i++)
		{
			collageData.push_back(Pixel::BLACK_PIXEL);
		}
	}

	// after that, write the bigger image
	for (size_t y = 0; y < bottomImageHeight; y++)
	{
		for (size_t x = 0; x < bottomImageWidth; x++)
		{
			index = y * bottomImageWidth + x;
			collageData.push_back(bottomImageData[index]);
		}
	}

	size_t newMaxValuePerPixel = (img1->maxValuePerPixel > img2->maxValuePerPixel) ? img1->maxValuePerPixel : img2->maxValuePerPixel;
	return new Image(img1->type, img1->magicNumber, newWidth, newHeight, newMaxValuePerPixel, collageData);
}

