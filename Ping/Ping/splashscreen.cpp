#include "StdAfx.h"
#include "SplashScreen.h"


bool SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Image image;
	if(image.LoadFromFile("images/SplashScreen.png") != true)
	{
		return false;
	}

	sf::Sprite sprite(image);

	renderWindow.Draw(sprite);
	renderWindow.Display();

	sf::Event event;
	while(true)
	{
		while(renderWindow.GetEvent(event))
		{
			if (event.Type == sf::Event::EventType::KeyPressed || event.Type == sf::Event::EventType::MouseButtonPressed)
			{
				return true;
			}

			if(event.Type == sf::Event::EventType::Closed)
			{
				return false;
			}
		}
	}
}