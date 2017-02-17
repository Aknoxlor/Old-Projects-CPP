#pragma once
#include "GameState.h"

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void HandleAllInputs();
	void UpdateAll();
	void DrawAll(sf::RenderWindow &renderWindow);

	GameState* Get(GameState::GameStateType type) const;

	void Add(GameState::GameStateType type, GameState* state);
	void Remove(GameState::GameStateType type);

private:
	std::map<GameState::GameStateType, GameState*> _gameStates;

	struct StateDeallocator
	{
		void operator()(const std::pair<GameState::GameStateType, GameState*> & p) const
		{
			delete p.second;
		}
	};
};