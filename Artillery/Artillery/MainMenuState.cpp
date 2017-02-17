#include "stdafx.h"
#include "MainMenuState.h"
#include "Game.h"

MainMenuState::MainMenuState()
{
	_graphicObject.Load("images/Lol.png");
	_gameStateType = ShowingMenu;

	/*
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
	*/

	//_menuItems.push_back(playButton);
	//_menuItems.push_back(exitButton);

}

MainMenuState::~MainMenuState()
{

}



void MainMenuState::HandleInput()
{
	if(_isInputting)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			GameEngine::GetGameStateManager().Get(ShowingMenu)->Pause();
			GameEngine::GetGameStateManager().Get(Playing)->Resume();
			GameEngine::_frameClock.restart();
		}
	}
}

void MainMenuState::Update()
{

}

void MainMenuState::Draw(sf::RenderWindow &renderWindow)
{
	if (_isDrawing)
	{
		if(_graphicObject.IsLoaded())
			_graphicObject.Draw(renderWindow);
		else
			_graphicObject.Load("images/Lol.png");
	}
}



MainMenuState::MenuResult MainMenuState::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator itClick;

	for ( itClick = _menuItems.begin(); itClick != _menuItems.end(); itClick++)
	{
		 sf::Rect<int> menuItemRect = (*itClick).rect;
		  if((menuItemRect.height + menuItemRect.top) > y && menuItemRect.top < y && menuItemRect.left < x && (menuItemRect.width + menuItemRect.left) > x)
		  {
			  return (*itClick).action;
		  }
	}
	return Nothing;
}
