#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "playerpaddle.h"
#include "gameball.h"
#include "objectmanager.h"

class GameEngine
{

public:
  static void Start();

  const static sf::Input& GetInput();
  static sf::RenderWindow& GetWindow();

  const static int SCREEN_WIDTH = 1024;
  const static int SCREEN_HEIGHT = 768;

private:
  static bool IsExiting();
  static void GameLoop();

  static void ShowSplashScreen();
  static void ShowMenu();



  enum GameState {Uninitialized,ShowingSplash,Paused, 
          ShowingMenu,Playing,Exiting};
  
  static GameState _gameState;
  static sf::RenderWindow _mainWindow;

  static ObjectManager _objectManager;
};
