#pragma once
//#include "SFML/Window.hpp"
//#include "SFML/Graphics.hpp"
//#include "stdafx.h"


class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);

	virtual void HandleInput();
	virtual void Update(sf::Time elapsedTime);
	virtual void Draw(sf::RenderWindow &window);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(sf::Vector2f pos);
	virtual void SetLayer(int layer);

	virtual sf::Vector2f GetPosition() const;
	virtual sf::Vector2f GetScale() const;
	virtual float GetAngle() const;
	virtual int GetLayer() const;

	virtual bool IsLoaded() const;
	virtual bool IsDeleted() const;

	virtual void Delete();

protected:	
	sf::Sprite _sprite;
	float _elapsedTimeSinceStart;

	int _layer;

private:
	bool _isLoaded;
	bool _isDeleted;
};