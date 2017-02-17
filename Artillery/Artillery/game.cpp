
#include "stdafx.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include "Players.h"
#include "Enemies.h"
#include "Game.h"

void GameEngine::Start(void)
{
	if(_gameState != NULL)
    return;

	std::srand((unsigned int)std::time(NULL));

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Bombard");
	//_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH*1.5, SCREEN_HEIGHT*1.5, 32),"Bombard");
	//_mainWindow.GetDefaultView().SetFromRect(sf::FloatRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));

	_gameStateManager.Add(GameState::ShowingMenu, new MainMenuState);
	_gameStateManager.Add(GameState::Playing, new PlayingState);
	_gameStateManager.Get(GameState::Playing)->Pause();

	_imageManager.Load("images/Cannon A.png");
	_imageManager.Load("images/Bullets.png");
	_imageManager.Load("images/Enemy A.png");
	_imageManager.Load("images/Background.png");
	_imageManager.Load("images/Health Bar Outline 1.png");
	_imageManager.Load("images/Lol.png");

	_background.Load("images/Background.png");

	Player_1 *player = new Player_1(sf::Vector2f((SCREEN_WIDTH/2)-20,250), 0);
	_objectManager.AddTagged("Cannon", player);

	Enemy_1 *enemy = new Enemy_1(sf::Vector2f((SCREEN_WIDTH/2)-170,100), 315);
	_objectManager.Add(enemy);

	enemy = new Enemy_1(sf::Vector2f((SCREEN_WIDTH/2)+150,100), 225);
	_objectManager.Add(enemy);

	enemy = new Enemy_1(sf::Vector2f((SCREEN_WIDTH/2)-170,500), 45);
	_objectManager.Add(enemy);

	enemy = new Enemy_1(sf::Vector2f((SCREEN_WIDTH/2)+150,500), 135);
	_objectManager.Add(enemy);

	while(!_isExiting)
	{
		GameLoop();
	}

	_mainWindow.close();
	delete _gameState;
}



const GameStateManager& GameEngine::GetGameStateManager()
{
	return _gameStateManager;
}

ObjectManager& GameEngine::GetObjectManager()
{
	return _objectManager;
}

const ImageManager& GameEngine::GetImageManager()
{
	return _imageManager;
}

sf::RenderWindow& GameEngine::GetWindow()
{
	return _mainWindow;
}



void GameEngine::AddDynamicObject(VisibleGameObject *object)
{
	_objectManager.Add(object);
}



void GameEngine::ExitGame()
{
	_isExiting = true;
}



void GameEngine::GameLoop()
{
	_mainWindow.clear(sf::Color(10,10,50));
	_background.Draw(_mainWindow);
	_gameStateManager.HandleAllInputs();
	_gameStateManager.UpdateAll();
	_gameStateManager.DrawAll(_mainWindow);
	_objectManager.MemoryManage();
	_mainWindow.display();

	sf::Event currentEvent;
	while(_mainWindow.pollEvent(currentEvent))
	{
		if(currentEvent.type == sf::Event::Closed)
		{
			ExitGame();
		}
	}
}


//Intilizations
bool GameEngine::_isExiting = false;
GameState* GameEngine::_gameState;

sf::RenderWindow GameEngine::_mainWindow;
sf::Clock GameEngine::_frameClock;

GameStateManager GameEngine::_gameStateManager;
ObjectManager GameEngine::_objectManager;
ImageManager GameEngine::_imageManager;

VisibleGameObject GameEngine::_background;

/*
	#include <iostream>
	
	float secondsiii = 0; //Debug global

	secondsiii += _frameClock.GetElapsedTime();

	if(secondsiii > 1.0f)
	{
		std::cout << (1.0f / (_mainWindow.GetFrameTime())) << " " <<(_objectManager.GetObjectCount() + _objectManager.GetObjectCount());
		std::cout << "  " << '\r';
		std::cout.flush();
		secondsiii -= 1.0f;
	}
*/