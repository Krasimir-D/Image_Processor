#pragma once
#include <cstdint>

#pragma pack(push, 1)
struct BmpFileHeader
{
	uint16_t file_type{ 0x4D42 }; // file ioObject is always BM which is 0x4D42
	uint32_t file_size{ 0 }; // size of the file (in bytes)
	uint16_t reserved1{ 0 }; // reserved, always 0
	uint16_t reserved2{ 0 }; // reserved, always 0
	uint32_t offset_data{ 0 }; // start position of pixel data (bytes from the begining)
};
#pragma pack(pop)

// from the following we consider only the width, height, bit_count and compression
struct BmpInfoHeader
{
	uint32_t size{ 0 }; // size of this header (in bytes)
	int32_t width{ 0 };	// width of the bitmap in pixels
	int32_t height{ 0 }; // height of the bitmap in pixels
	// (if positive, bottom-up. with origin in the lower left corner)
	// (if negative, top-down. with origin in the upper left corner)

	uint16_t planes{ 1 }; // No. of planes for the target device, this is always 1
	uint16_t bit_count{ 0 }; // No. of bits per pixel
	uint32_t compression{ 0 }; // 0 or 3- uncompressed. This program only considers uncompressed images
	uint32_t size_image{ 0 }; // 0- for uncompressed images
	int32_t x_pixels_per_meter{ 0 };
	int32_t y_pixels_per_meter{ 0 };
	uint32_t colors_used{ 0 }; // No. of indexes in the color table. Use 0 for the max number of colors
	uint32_t colors_important{ 0 }; // No. of colors used for displaying the bitmap
};