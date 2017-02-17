#pragma once

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

	virtual void Pause();
	virtual void Resume();

	virtual void SetUpdating(bool input);
	virtual void SetDrawing(bool input);
	virtual void SetInputting(bool input);

	const GameStateType GetType() const;

protected:
	GameState();

	GameStateType _gameStateType;
	bool _isUpdating;
	bool _isDrawing;
	bool _isInputting;
};