#pragma once
#include "GameState.h"
#include "VisibleGameObject.h"
//#include "SFML/Window.hpp"
//#include "SFML/Graphics.hpp"
//#include "stdafx.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();

	void HandleInput();
	void Update();
	void Draw(sf::RenderWindow& window);

private:
	enum MenuResult 
	{
		Nothing,
		Exit, 
		Play, 
		Options
	};

	struct MenuItem
	{
		sf::IntRect rect;
		MenuResult action;
	};

	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
	VisibleGameObject _graphicObject;
};

