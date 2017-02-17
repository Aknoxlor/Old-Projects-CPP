#pragma once
#include "GameState.h"

class PlayingState : public GameState
{
public:
	PlayingState();
	~PlayingState();

	void HandleInput();
	void Update();
	void Draw(sf::RenderWindow &renderWindow);
};