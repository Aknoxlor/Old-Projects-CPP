#pragma once
#include "AbstractEnemy.h"

class Enemy_1 :
	public AbstractEnemy
{
public:
	Enemy_1(sf::Vector2f position, float angle, float speed = 75.0f);
	~Enemy_1();

	void Damage(unsigned int damageAmount);
};

class Enemy_2 :
	public AbstractEnemy
{
public:
	Enemy_2(sf::Vector2f position, float angle, float speed = 150.0f);
	~Enemy_2();

	void Damage(unsigned int damageAmount);
};

class Enemy_3 :
	public AbstractEnemy
{
public:
	Enemy_3(sf::Vector2f position, float angle, float speed = 200.0f);
	~Enemy_3();

	void Damage(unsigned int damageAmount);
};