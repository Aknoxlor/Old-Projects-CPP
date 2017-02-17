#pragma once
//include "SFML/Window.hpp"
//#include "SFML/Graphics.hpp"

class GameState
{
public:
	virtual ~GameState() ;

	enum GameStateType
	{
		Uninitialized,
		Paused, 
		ShowingMenu,
		Playing,
		Exiting
	};

	virtual void HandleInput() = 0;
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow &renderWindow) = 0;

	virtual void Pause(bool input = true, bool update = true, bool draw = true);
	virtual void Resume(bool input = true, bool update = true, bool draw = true);


	const GameStateType GetType() const;

protected:
	GameState();

	GameStateType _gameStateType;
	bool _isPaused[3];
};