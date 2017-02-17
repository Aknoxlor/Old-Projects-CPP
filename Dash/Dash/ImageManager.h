#pragma once

class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	void Load(std::string filename);
	void Remove(std::string name);

	sf::Texture* Get(std::string name) const;

private:
	std::map<std::string, sf::Texture*> _images;

	struct ImageDeallocator
	{
		void operator()(const std::pair<std::string, sf::Texture*> & p) const
		{
			delete p.second;
		}
	};
};