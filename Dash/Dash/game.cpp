
#include "stdafx.h"
#include "Game.h"
#include "ObjectManager.h"



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
	_gameStateManager.Get(GameState::Playing)->Resume();


	_imageManager.Load("images/Background.png");
	_imageManager.Load("images/Dot.png");

	_background.Load("images/Background.png");

	_objectManager.MemoryManage();

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

const ObjectManager& GameEngine::GetObjectManager()
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
	_objectManager.AddDynamic(object);
}



void GameEngine::ExitGame()
{
	_isExiting = true;
}



void GameEngine::GameLoop()
{
	_mainWindow.clear(sf::Color(0,0,0));
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
		std::cout << (1.0f / (_mainWindow.GetFrameTime())) << " " <<(_objectManager.GetObjectCount() + _objectManager.GetDynamicCount());
		std::cout << "  " << '\r';
		std::cout.flush();
		secondsiii -= 1.0f;
	}
*/