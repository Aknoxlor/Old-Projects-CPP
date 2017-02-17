#include "stdafx.h"
#include "AbstractProjectile.h"
#include "Game.h"
#include "AbstractTurret.h"

void AbstractTurret::HandleInput()
{
	sf::Vector2f mousePos(sf::Mouse::getPosition(GameEngine::GetWindow()).x, sf::Mouse::getPosition(GameEngine::GetWindow()).y);
	sf::Vector2f pos = _sprite.getPosition();
	_mouseAngle = GMath::TurnTowardsPoint(pos, mousePos, _angle, 10.0f);
	_angle = GMath::TurnTowardsPoint(pos, mousePos) - 90;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		_isFiring = true;
	else
		_isFiring = false;
}

void AbstractTurret::Update(sf::Time elapsedTime)
{
	_elapsedTime = elapsedTime.asSeconds();
	_elapsedTimeSinceStart += _elapsedTime;
	static float timer(-1.0);

	/*
	float difference = _angle - _mouseAngle;
	difference *= _elapsedTime;
	_angle += difference;
	*/

	_sprite.setPosition(_vehicleMount->GetPosition());
	_velocity = _vehicleMount->GetVelocity();
	_sprite.setRotation(-_angle + 90);
	if(_isFiring)
	{
		if (timer < _elapsedTimeSinceStart)
		{
			VehicleObject *proj = NewProjectile(*this);
			assert(proj->GetType() == VehicleObject::projectile);
			GameEngine::AddDynamicObject(proj);
			timer = _elapsedTimeSinceStart + _fireRate;
		}
	}
}

void AbstractTurret::Sync(const VehicleObject *mount)
{
	_angle = mount->GetAngle();
	_sprite.setPosition(mount->GetPosition());
	_velocity = mount->GetVelocity();
	_sprite.setRotation(-_angle + 180.0f);
	_vehicleMount = mount;
}


AbstractTurret::AbstractTurret(const VehicleObject *mount, const float fireRate)
	:VehicleObject(0.0f, 0.0f, 10, 0.0f, turret), _fireRate(fireRate), _isFiring(false)
{
	_layer = 3;
	Sync(mount);
}

AbstractTurret::AbstractTurret(const float fireRate)
	:VehicleObject(0.0f, 0.0f, 10, 0.0f, turret), _fireRate(fireRate), _isFiring(false)
{
	_layer = 3;
}

AbstractTurret::~AbstractTurret()
{
}