#include "stdafx.h"
#include "game.h"
#include "splashscreen.h"
#include "mainmenu.h"
#include "objectmanager.h"
//#include "visiblegameobject.h"

void GameEngine::Start(void)
{

	if(_gameState != Uninitialized)
    return;

	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Ping!");
	
	PlayerPaddle *player1 = new PlayerPaddle;
	player1->SetPosition((SCREEN_WIDTH/2)-45,700);

	GameBall *ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2)-15);

	_objectManager.Add("Paddle1",player1);
	_objectManager.Add("Ball",ball);
	
	_gameState = GameEngine::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.Close();

}

bool GameEngine::IsExiting()
{
	
	if(_gameState == GameEngine::Exiting) 
		return true;
	else 
		return false;

}

void GameEngine::ShowSplashScreen()
{
	SplashScreen splashScreen;
	if(splashScreen.Show(_mainWindow))
		_gameState = GameEngine::ShowingMenu;
	else
		_gameState = GameEngine::Exiting;
}

void GameEngine::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
		case MainMenu::Exit:
		_gameState = GameEngine::Exiting;
		break;

		case MainMenu::Play:
		_gameState = GameEngine::Playing;
		break;
	}
}

const sf::Input& GameEngine::GetInput()
{
	return _mainWindow.GetInput();
}

sf::RenderWindow& GameEngine::GetWindow()
{
	return _mainWindow;
}

void GameEngine::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);
		switch(_gameState)
		{
		case GameEngine::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}

		case GameEngine::ShowingMenu:
			{
				ShowMenu();
				break;
			}

		case GameEngine::Playing:
			{
				//sf::Event currentEvent;
				//while(_mainWindow.GetEvent(currentEvent))
				{
					_mainWindow.Clear(sf::Color(0,0,0));
					_objectManager.UpdateAll();
					_objectManager.DrawAll(_mainWindow);
					_mainWindow.Display();

					if(currentEvent.Type == sf::Event::Closed)
					{
						_gameState = GameEngine::Exiting;
					}
					if(currentEvent.Type == sf::Event::KeyPressed)
					{
						if(currentEvent.Key.Code == sf::Key::Escape)
						_gameState = GameEngine::ShowingMenu;
					}
				}
				break;
			}
			//default:
				//break;
		}
}

GameEngine::GameState GameEngine::_gameState = Uninitialized;
sf::RenderWindow GameEngine::_mainWindow;
ObjectManager GameEngine::_objectManager;