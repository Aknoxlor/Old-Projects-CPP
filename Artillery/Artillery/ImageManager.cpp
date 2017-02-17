#include "stdafx.h"
#include "ImageManager.h"

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{
	std::for_each(_images.begin(),_images.end(),ImageDeallocator());
}



void ImageManager::Load(std::string filename)
{
	sf::Texture* tex = new sf::Texture;
	assert(tex->loadFromFile(filename) == true);
		_images.insert(std::pair<std::string, sf::Texture*>(filename, tex));
}

void ImageManager::Remove(std::string name)
{
	std::map<std::string, sf::Texture*>::iterator results = _images.find(name);
	if (results != _images.end())
	{
		delete results->second;
		_images.erase(results);
	}
}



sf::Texture* ImageManager::Get(std::string name) const
{
	std::map<std::string, sf::Texture*>::const_iterator results = _images.find(name);
	if (results == _images.end())
		return NULL;
	return results->second;
}