#pragma once
#include "ObjectManager.h"
#include "ImageManager.h"
#include "GameStateManager.h"

class GameEngine
{
public:
	static void Start();

	static ObjectManager& GetObjectManager();
	const static ImageManager& GetImageManager();
	const static GameStateManager& GetGameStateManager();
	static sf::RenderWindow& GetWindow();

	static void AddDynamicObject(VisibleGameObject *object);

	const static int SCREEN_WIDTH = 768; // 512 * 1.5
	const static int SCREEN_HEIGHT = 576; // 384 * 1.5
	static sf::Clock _frameClock;

private:
	static void ExitGame();
	static void GameLoop();
  
	static bool _isExiting;

	static GameState* _gameState;
	static sf::RenderWindow _mainWindow;
	static VisibleGameObject _background;

	static ObjectManager _objectManager;
	static ImageManager _imageManager;
	static GameStateManager _gameStateManager;
};
