#pragma once
#include "HeterogenicArray.hpp"
#include <cassert>

class ImageIOFactory
{
public:
	static ImageIOFactory& getFactory()
	{
		static ImageIOFactory instance;
		return instance;
	}

	void registerImageImporter(const ImageImporter* importer)
	{
		importers.push_back(importer);
	}

	void registerImageExporter(const ImageExporter* exporter)
	{
		exporters.push_back(exporter);
	}

	Image* load(const char* path) const
	{
		char magicNumber[3] = {'\0'};
		std::ifstream in(path);
		if (!in)
		{
			std::cerr << "Unable to open file for reading! Make sure whether file with name /""" << path << "/"" exists!\n";
			throw std::runtime_error("Unable to open file for reading!");
		}
		in.getline(magicNumber, 3);
		magicNumber[2] = '\0';
		in.clear(); // Clear any error flags that might be set
		in.seekg(0, std::ios::beg);
		in.close();
		
		// THE FACTORY CHOOSES THE IMPORTER BASED ON MAGIC NUMBER FOR FOOLPROOFING
		const ImageImporter* importer = getImporter(magicNumber);
		if (!importer)
		{
			throw std::runtime_error("Unsupported file format!");
		}

		Image* result = importer->loadImage(path, magicNumber);
		result->setPath(path);
		return result;
	}

	void save(const Image& img) const
	{
		const ImageExporter* exporter = getExporter(img);
		if (!exporter)
		{
			throw std::runtime_error("Unable to find suitable exporter!");
		}

		exporter->saveImage(img.getPath().c_str(), img);
	}

private:		
	std::vector<const ImageImporter*> importers;
	std::vector<const ImageExporter*> exporters;

	ImageIOFactory() = default;	
	~ImageIOFactory() = default;
	ImageIOFactory(const ImageIOFactory&) = delete;
	ImageIOFactory& operator=(const ImageIOFactory&) = delete;

	const ImageImporter* getImporter(const char* magicNumber) const
	{
		for (size_t i = 0; i < importers.size(); i++)
		{
			if (importers[i]->isFormatSupported(magicNumber))
				return importers[i];
		}
		return nullptr;
	}

	const ImageExporter* getExporter(const Image& img) const
	{
		for (size_t i = 0; i < exporters.size(); i++)
		{
			if (exporters[i]->isFormatSupported(img.getMagicNumber()))
				return exporters[i];
		}		
		return nullptr;
	}
};

