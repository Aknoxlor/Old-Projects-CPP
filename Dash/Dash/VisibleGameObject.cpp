#include "StdAfx.h"
#include "VisibleGameObject.h"
#include "Game.h"


VisibleGameObject::VisibleGameObject():
	_elapsedTimeSinceStart(0.0f), _layer(0), _isLoaded(false), _isDeleted(false)
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

void VisibleGameObject::SetLayer(int layer)
{
	if(_isLoaded)
		_layer = layer;
}



sf::Vector2f VisibleGameObject::GetPosition() const
{
	if(_isLoaded)
		return _sprite.getPosition();
	return sf::Vector2f();
}

sf::Vector2f VisibleGameObject::GetScale() const
{
	if(_isLoaded)
		return _sprite.getScale();
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
	if(_isLoaded)
		return _layer;
	return 0;
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