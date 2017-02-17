#pragma once
#include "AbstractProjectile.h"

class Projectile :
	public AbstractProjectile
{
public:
	Projectile(const VehicleObject &origin);
	~Projectile();
	void Draw(sf::RenderWindow& rw);
};