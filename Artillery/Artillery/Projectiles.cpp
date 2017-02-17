#include "stdafx.h"
#include "Projectiles.h"

Projectile::Projectile(const VehicleObject &origin):
AbstractProjectile(origin, 300, 500)
{
	Load("images/Bullets.png"); 
	assert(IsLoaded());

	sf::IntRect rect(1, 1, 81, 31);
	_sprite.setTextureRect(rect);
	_sprite.setOrigin(float(rect.width) / 2, float(rect.height) / 2);

	_sprite.setScale(0.3, 0.3);

	_target = enemy;
}

Projectile::~Projectile()
{
}

void Projectile::Draw(sf::RenderWindow& rw)
{	
	//GetBoundingBox().Draw(rw);
	VisibleGameObject::Draw(rw);
}
