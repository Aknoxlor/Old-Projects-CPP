#include "stdafx.h"
#include "VehicleObject.h"
#include "Game.h"

VehicleObject::VehicleObject():
	_maxVelocity(0), _drag(0), _maxHealth(0), _turnSpeed(0), _vehicleType(undefined)
{

}

VehicleObject::VehicleObject(const float maxVelocity, const float drag, const int maxHealth, const float turnSpeed, const VehicleType vehicleType):
	_drag(drag), _maxVelocity(maxVelocity), _maxHealth(maxHealth), _vehicleType(vehicleType), _health(maxHealth), _turnSpeed(turnSpeed)
{

}

VehicleObject::~VehicleObject()
{
}



sf::Vector2f VehicleObject::GetVelocity() const
{
	return _velocity;
}

float VehicleObject::GetAngle() const
{
	return _angle;
}

GMath::OriBoundingBox VehicleObject::GetBoundingBox() const
{
	if(IsLoaded())
	{
		return GMath::OriBoundingBox(_sprite.getPosition(), _sprite.getLocalBounds().width * _sprite.getScale().x, _sprite.getLocalBounds().height *  _sprite.getScale().y, _angle);
	}
	return GMath::OriBoundingBox(sf::Vector2f(),0,0,0);
}

VehicleObject::VehicleType VehicleObject::GetType() const
{
	return _vehicleType;
}



void VehicleObject::Damage(unsigned int damageAmount)
{
	/*
	_health -= damageAmount;
	if(_health <= 0)
		Delete();
	*/
}

void VehicleObject::Repair(unsigned int repairAmount)
{
	/*
		_health += repairAmount;
	if(_health > _maxHealth)
		_health = _maxHealth;
	*/
}


/*void VehicleObject::UpdateVelocity()
{
	if (_speed > 0)
		_speed -= _drag;  
	else if(_speed < 0)
		_speed += _drag;

	if (_speed > _maxVelocity)
		_speed = _maxVelocity;
	else if (_speed < -_maxVelocity)
		_speed = -_maxVelocity;
}*/