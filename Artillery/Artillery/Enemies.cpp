#include "stdafx.h"
#include "Game.h"
#include "Enemies.h"

Enemy_1::Enemy_1(sf::Vector2f position, float angle, float speed): 
 AbstractEnemy(75.0f, 0.1f, 50)
{
	Load("images/Enemy A.png");
	assert(IsLoaded());

	_speed = speed;
	_angle = angle;
	//_sprite2 = _sprite;

	sf::IntRect rect(21, 37, 20, 22);
	_sprite.setTextureRect(rect);
	_sprite.setOrigin(float(rect.width) / 2, float(rect.height) / 2);

	_sprite.setPosition(position);
	_sprite.setRotation(_angle);
}

Enemy_1::~Enemy_1()
{

}

void Enemy_1::Damage(unsigned int damageAmount)
{
	_health -= damageAmount;

	if(_health <= 0)
	{
		Delete();
		Enemy_2 *enemy = new Enemy_2(_sprite.getPosition(), _angle, _speed);
		GameEngine::AddDynamicObject(enemy);
	}
	else
		_healthBar.SetScale(float(_health) / float(_maxHealth));
}



Enemy_2::Enemy_2(sf::Vector2f position, float angle, float speed): 
 AbstractEnemy(150.0f, 0.1f, 25)
 {
	Load("images/Enemy A.png");
	assert(IsLoaded());

	_speed = speed;
	_angle = angle;
	//_sprite2 = _sprite;

	sf::IntRect rect(21, 37, 20, 22);
	_sprite.setTextureRect(rect);
	_sprite.setOrigin(float(rect.width) / 2, float(rect.height) / 2);

	_sprite.setRotation(_angle);
	_sprite.setPosition(position);

	_sprite.scale(15.0 / 20.0, 17.0 / 22.0);
 }

 Enemy_2::~Enemy_2()
{

}

 void Enemy_2::Damage(unsigned int damageAmount)
{
	_health -= damageAmount;

	if(_health <= 0)
	{
		Delete();
		for(int iii(0); iii < 3; iii++)
		{
			sf::Vector2f random((std::rand() % 10 + 1), (std::rand() % 10 + 1));
			random += _sprite.getPosition();
			Enemy_3 *enemy = new Enemy_3(random, _angle + (std::rand() % 30 - 14), _speed);
			GameEngine::AddDynamicObject(enemy);
		}
	}
	else
		_healthBar.SetScale(float(_health) / float(_maxHealth));
}



 Enemy_3::Enemy_3(sf::Vector2f position, float angle, float speed): 
 AbstractEnemy(200.0f, 0.1f, 10)
 {
	Load("images/Enemy A.png");
	assert(IsLoaded());

	_speed = speed;
	_angle = angle;
	//_sprite2 = _sprite;

	sf::IntRect rect(21, 37, 20, 22);
	_sprite.setTextureRect(rect);
	_sprite.setOrigin(float(rect.width) / 2, float(rect.height) / 2);

	_sprite.setRotation(_angle);
	_sprite.setPosition(position);

	_sprite.scale(15.0 / 20.0, 12.0 / 22.0);
 }

 Enemy_3::~Enemy_3()
{

}

 void Enemy_3::Damage(unsigned int damageAmount)
{
	_health -= damageAmount;

	if(_health <= 0)
	{
		Delete();
		sf::Vector2f random((std::rand() % 450 + 1), (std::rand() % 450 + 1));
		Enemy_1 *enemy = new Enemy_1(random, (std::rand() % 360 + 1));
		GameEngine::AddDynamicObject(enemy);
	}
	else
		_healthBar.SetScale(float(_health) / float(_maxHealth));
}