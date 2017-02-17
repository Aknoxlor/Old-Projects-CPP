#pragma once
#include "GameState.h"

class NullState : public GameState
{
public:
	NullState();
	~NullState();

	void HandleInput(const sf::Input &input);
	void Update();
	void Draw(sf::RenderWindow &renderWindow);
};