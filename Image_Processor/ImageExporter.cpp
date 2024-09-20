#include "ImageExporter.h"
#include "ImageIOFactory.hpp"

ImageExporter::ImageExporter()
{
	ImageIOFactory::getFactory().registerImageExporter(this);
}
