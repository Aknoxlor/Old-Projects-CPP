#include "stdafx.h"
#include "Game.h"
#include "AbstractProjectile.h"

void AbstractProjectile::Update(sf::Time elapsedTime)
{
	_elapsedTime = elapsedTime.asSeconds();
	_elapsedTimeSinceStart += _elapsedTime;

	_distanceTraveled += (_maxVelocity * _elapsedTime);
	if(_distanceTraveled > _maxRange)
	{
		Delete();
		return;
	}

	_sprite.move(_velocity.x * _elapsedTime, _velocity.y * _elapsedTime);
	
	CollisionDetection();
}



AbstractProjectile::AbstractProjectile(const VehicleObject &origin, const float maxVelocity, const int maxRange, const float drag, const int maxHealth)
	: VehicleObject(maxVelocity, drag, maxHealth, 0.0f, projectile), _maxRange(maxRange), _distanceTraveled(0)
{
	_sprite.setPosition(origin.GetPosition());
	_angle = origin.GetAngle() + (std::rand() % 20 - 9);
	_sprite.setRotation(-_angle);

	sf::Vector2f newVelocity = GMath::CreateVector(_maxVelocity, _angle);
	_velocity.x = origin.GetVelocity().x + newVelocity.x;
	_velocity.y = origin.GetVelocity().y + newVelocity.y;

	_layer = 2;
}

AbstractProjectile::~AbstractProjectile()
{

}



void AbstractProjectile::CollisionDetection()
{
	VehicleObject* vehicle;
	for(unsigned int iii(0); iii < GameEngine::GetObjectManager().GetObjectCount(); iii++)
	{
		vehicle = dynamic_cast<VehicleObject*>(GameEngine::GetObjectManager().Get(iii));
		if (vehicle != NULL && vehicle->GetType() == _target)
		{
			if (vehicle->GetBoundingBox().CollisionCheck(GetBoundingBox())) //REALLY BAD collision detection
			{
				/*
				if((vehicle->GetHealth()) >= _health)
					Delete();
				else
					Damage(vehicle->GetHealth());
				*/
				Delete();
				vehicle->Damage(10);
				return;
			}
		}
	}
}