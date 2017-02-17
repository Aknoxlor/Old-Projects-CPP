#include "stdafx.h"
#include "GameState.h"

GameState::GameState() : _isUpdating(true), _isDrawing(true), _isInputting(true)
{
	_gameStateType = Uninitialized;
}

GameState::~GameState()
{

}



void GameState::Pause()
{
	_isUpdating = false;
	_isDrawing = false;
	_isInputting = false;
}

void GameState::Resume()
{
	_isUpdating = true;
	_isDrawing = true;
	_isInputting = true;
}



void GameState::SetUpdating(bool input)
{
	_isUpdating = input;
}

void GameState::SetDrawing(bool input)
{
	_isDrawing = input;
}

void GameState::SetInputting(bool input)
{
	_isInputting = input;
}



const GameState::GameStateType GameState::GetType() const
{
	return _gameStateType;
}