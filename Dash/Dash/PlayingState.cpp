#include "stdafx.h"
#include "PlayingState.h"
#include "Game.h"

PlayingState::PlayingState()
{
	_gameStateType = Playing;
}

PlayingState::~PlayingState()
{

}



void PlayingState::HandleInput()
{
	if (!_isPaused[0])
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			GameEngine::GetGameStateManager().Get(Playing)->Pause();
			GameEngine::GetGameStateManager().Get(ShowingMenu)->Resume();
		}
	}
}

void PlayingState::Update()
{
	if (!_isPaused[1])
	GameEngine::GetObjectManager().UpdateAll();
}

void PlayingState::Draw(sf::RenderWindow &renderWindow)
{
	if (!_isPaused[2])
	GameEngine::GetObjectManager().DrawAll(renderWindow);
}