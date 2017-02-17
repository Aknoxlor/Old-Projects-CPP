#include "stdafx.h"
#include "ScalingBar.h"

ScalingBar::ScalingBar() : _scale(1.0f)
{
	Load("images/Health Bar Outline 1.png");
	assert(IsLoaded());

	_sprite.setOrigin(_sprite.getScale().x/2, _sprite.getScale().y/2);
	_dynamicBar = sf::RectangleShape(sf::Vector2f(22.0f,5.0f));
	_dynamicBar.setFillColor(sf::Color(200,0,0));
	_dynamicBar.setOrigin(0.0, 0.0);
}

ScalingBar::~ScalingBar()
{

}



void ScalingBar::Draw(sf::RenderWindow &rw)
{
	//sf::Vector2f pos = _sprite.getTransform().transformPoint( _sprite.getPosition());
	//pos.x =  11.0f * _scale;
	_dynamicBar.setPosition(_sprite.getPosition());
	_dynamicBar.move(2.0f, 0.0f);

	rw.draw(_dynamicBar);
	VisibleGameObject::Draw(rw);
}



void ScalingBar::SetScale(float percentage)
{
	float _percentage = abs(percentage);
	if (_percentage < 1.0f)
	{
		_dynamicBar.setScale(_percentage, 1.0f);
		_scale = _percentage;
	}
	else
	{
		_dynamicBar.setScale(1.0f, 1.0f);
		_scale = 1.0f;
	}
}