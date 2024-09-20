#pragma once
#include <iostream>

struct Pixel
{
	//def ctor, creating (0,0,0) pixel
	Pixel() 
		: red(0), green(0), blue(0) {}
	//ctor with parameters
	Pixel(uint8_t red, uint8_t green, uint8_t blue)
		: red(red), green(green), blue(blue) {}

	uint8_t getLuminance() const;
	Pixel getCompliment() const;

	bool operator == (const Pixel& other) const;

	friend std::ostream& operator<<(std::ostream& out, const Pixel& pixel);

	uint8_t red;
	uint8_t green;
	uint8_t blue;

	static const Pixel WHITE_PIXEL; // pixel with values (255, 255, 255)
	static const Pixel BLACK_PIXEL; // pixel with values (0, 0, 0)
	static const Pixel PADDING_PIXEL; // pixel with values (69, 69, 69)
};




