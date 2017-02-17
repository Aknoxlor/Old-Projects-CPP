#include "stdafx.h"
#include "GameStateManager.h"

GameStateManager::GameStateManager()
{

}

GameStateManager::~GameStateManager()
{
	std::for_each(_gameStates.begin(), _gameStates.end(), StateDeallocator());
}

void GameStateManager::HandleAllInputs()
{
	std::map<GameState::GameStateType, GameState*>::const_iterator itr = _gameStates.begin();
	while(itr != _gameStates.end())
	{
		itr->second->HandleInput();
		itr++;
	}
}

void GameStateManager::UpdateAll()
{
	std::map<GameState::GameStateType, GameState*>::const_iterator itr = _gameStates.begin();
	while(itr != _gameStates.end())
	{
		itr->second->Update();
		itr++;
	}
}

void GameStateManager::DrawAll(sf::RenderWindow &renderWindow)
{
	std::map<GameState::GameStateType, GameState*>::const_iterator itr = _gameStates.begin();
	while(itr != _gameStates.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}



GameState* GameStateManager::Get(GameState::GameStateType type) const
{
	std::map<GameState::GameStateType, GameState*>::const_iterator results = _gameStates.find(type);
	if (results == _gameStates.end())
		return NULL;
	return results->second;
}



void GameStateManager::Add(GameState::GameStateType type, GameState* state)
{
	_gameStates.insert(std::pair<GameState::GameStateType, GameState*>(type, state));
}

void GameStateManager::Remove(GameState::GameStateType type)
{
	std::map<GameState::GameStateType, GameState*>::iterator results = _gameStates.find(type);
	if (results != _gameStates.end())
	{
		delete results->second;
		_gameStates.erase(results);
	}
}
