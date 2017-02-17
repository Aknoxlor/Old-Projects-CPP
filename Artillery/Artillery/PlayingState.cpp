#include "stdafx.h"
#include "Game.h"
#include "PlayingState.h"

PlayingState::PlayingState()
{
	_gameStateType = Playing;
}

PlayingState::~PlayingState()
{

}



void PlayingState::HandleInput()
{
	if (_isInputting)
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
	if (_isUpdating)
	{
		sf::Time timeDelta = GameEngine::_frameClock.restart();
		GameEngine::GetObjectManager().IterateAll([&](VisibleGameObject* &obj){if(obj != NULL) obj->Update(timeDelta);});
	}
}

void PlayingState::Draw(sf::RenderWindow &renderWindow)
{
	if (_isDrawing)
		GameEngine::GetObjectManager().IterateAll([&](VisibleGameObject* &obj){if(obj != NULL) obj->Draw(renderWindow);});
}