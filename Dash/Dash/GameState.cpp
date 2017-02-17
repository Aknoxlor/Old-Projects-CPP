#include "stdafx.h"
#include "GameState.h"

GameState::GameState()
{
	_gameStateType = Uninitialized;
	for(int iii(0); iii < 3; iii++)
		_isPaused[iii] = true;
}

GameState::~GameState()
{

}



void GameState::Pause(bool input, bool update, bool draw)
{
	if (input)
		_isPaused[0] = true;
	if (update)
		_isPaused[1] = true;
	if (draw)
		_isPaused[2] = true;
}

void GameState::Resume(bool input, bool update, bool draw)
{
	if (input)
		_isPaused[0] = false;
	if (update)
		_isPaused[1] = false;
	if (draw)
		_isPaused[2] = false;
}



const GameState::GameStateType GameState::GetType() const
{
	return _gameStateType;
}