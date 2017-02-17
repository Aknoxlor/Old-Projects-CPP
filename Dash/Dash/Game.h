#pragma once

#include "ObjectManager.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include "ImageManager.h"
#include "GameState.h"
#include "GameStateManager.h"



class GameEngine
{
public:
	static void Start();

	const static ObjectManager& GetObjectManager();
	const static ImageManager& GetImageManager();
//	const static sf::Input& GetInput();
	const static GameStateManager& GetGameStateManager();
	static sf::RenderWindow& GetWindow();

	static void AddDynamicObject(VisibleGameObject *object);

	const static int SCREEN_WIDTH = 1024; // 512 * 1.5
	const static int SCREEN_HEIGHT = 768; // 384 * 1.5
	static sf::Clock _frameClock;

private:
	static void ExitGame();
	static void GameLoop();
  
	static bool _isExiting;
	static GameState* _gameState;

	static GameStateManager _gameStateManager;
	static sf::RenderWindow _mainWindow;

	static ObjectManager _objectManager;
	static ImageManager _imageManager;

	static VisibleGameObject _background;
};
