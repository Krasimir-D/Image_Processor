#include "ImageImporter.h"
#include "ImageIOFactory.hpp"

ImageImporter::ImageImporter()
{
	ImageIOFactory::getFactory().registerImageImporter(this);
}
