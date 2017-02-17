#include "stdafx.h"
#include "Vehicle.h"
#include "Game.h"

Vehicle::Vehicle():
	_maxVelocity(0), _velocity(0,0), _angle(0), _drag(0), _speed(0), _vehicleType(undefined)
{

}

Vehicle::Vehicle(float drag, float maxVelocity, float angle, float speed, VehicleType vehicleType):
	_maxVelocity(maxVelocity), _velocity(0,0), _angle(angle), _drag(drag), _speed(speed), _vehicleType(vehicleType)
{

}

Vehicle::~Vehicle()
{
}



const sf::Vector2f Vehicle::GetVelocity()
{
	return _velocity;
}

const sf::IntRect Vehicle::GetBoundingRect()
{
	if(IsLoaded())
	{
		sf::Vector2f size = _sprite.GetSize();
		sf::Vector2f position = _sprite.GetPosition();
		return sf::IntRect(position.x - size.x/2, position.y - size.y/2, position.x + size.x/2, position.y + size.y/2);
	}
	return sf::IntRect();
}

Vehicle::VehicleType Vehicle::GetType()
{
	return _vehicleType;
}

void Vehicle::DecrementHealth(int health)
{
	_health -= health;

	if(_health <= 0)
		Delete();
}



void Vehicle::UpdateVelocity()
{

	if (_speed > 0)
		_speed -= _drag;  
	else if(_speed < 0)
		_speed += _drag;

	_speed = GMath::LimitValue(_speed, _maxVelocity, (-_maxVelocity / 2));

	double angle = (_angle * 3.14159265 / 180);
	
	_velocity.y = sin(-angle) * _speed;
	_velocity.x = cos(-angle) * _speed;

}
