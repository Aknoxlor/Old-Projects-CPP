#include "StdAfx.h"
#include "Game.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject():
	_layer(0), _elapsedTimeSinceStart(0.0f), _isLoaded(false), _isDeleted(false)
{

}

VisibleGameObject::~VisibleGameObject()
{
}



void VisibleGameObject::Load(std::string filename)
{
	if(GameEngine::GetImageManager().Get(filename) == NULL)
	{
		//_filename = "";
		_isLoaded = false;
	}
	else
	{
		//_filename = filename
		_sprite.setTexture(*GameEngine::GetImageManager().Get(filename), true);
		_isLoaded = true;
	}
}



void VisibleGameObject::HandleInput()
{

}

void VisibleGameObject::Update(sf::Time elapsedTime)
{

}

void VisibleGameObject::Draw(sf::RenderWindow& rw)
{
	if(_isLoaded)
	{
		rw.draw(_sprite);
	}
}



void VisibleGameObject::SetPosition(float x, float y)
{
	if(_isLoaded)
		_sprite.setPosition(x,y);
}

void VisibleGameObject::SetPosition(sf::Vector2f pos)
{
	if(_isLoaded)
		_sprite.setPosition(pos);
}



sf::Vector2f VisibleGameObject::GetPosition() const
{
	if(_isLoaded)
		return _sprite.getPosition();
	return sf::Vector2f();
}

float VisibleGameObject::GetAngle() const
{
	if(_isLoaded)
		return _sprite.getRotation();
	return 0.0f;
}

int VisibleGameObject::GetLayer() const
{
	return _layer;
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}

bool VisibleGameObject::IsDeleted() const
{
	return _isDeleted;
}



void VisibleGameObject::Delete()
{
	_isDeleted = true;
}
