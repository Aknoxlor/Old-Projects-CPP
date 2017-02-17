#pragma once
#include "Projectile.h"

class Bullet_1 : 
	public Projectile
{
	Bullet_1(float angle, sf::Vector2f Position, sf::Vector2f Velocity);
	~Bullet_1();
}