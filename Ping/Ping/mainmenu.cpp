#include "stdafx.h"
#include "mainmenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	sf::Image image;
	image.LoadFromFile("images/MainMenu.png");
	sf::Sprite sprite(image);

	MenuItem playButton;
	playButton.rect.Top = 500;
	playButton.rect.Bottom = 585;
	playButton.rect.Left = 275;
	playButton.rect.Right = 450;
	playButton.action = Play;

	MenuItem exitButton;
	exitButton.rect.Top = 500;
	exitButton.rect.Bottom = 585;
	exitButton.rect.Left = 625;
	exitButton.rect.Right = 760;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.Draw(sprite);
	window.Display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator itClick;

	for ( itClick = _menuItems.begin(); itClick != _menuItems.end(); itClick++)
	{
		 sf::Rect<int> menuItemRect = (*itClick).rect;
		  if( menuItemRect.Bottom > y && menuItemRect.Top < y && menuItemRect.Left < x && menuItemRect.Right > x)
		  {
			  return (*itClick).action;
		  }
	}
	return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while(true)
	{
		while(window.GetEvent(menuEvent))
		{
			if (menuEvent.Type == sf::Event::EventType::MouseButtonPressed)
			{
				return HandleClick(menuEvent.MouseButton.X,menuEvent.MouseButton.Y);
			}
			
			if (menuEvent.Type == sf::Event::EventType::Closed)
			{
				return Exit;
			}
		}
	}
}
