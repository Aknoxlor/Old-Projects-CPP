#pragma once
#include "VisibleGameObject.h"

class Vehicle :
	public VisibleGameObject
{
public:
	enum VehicleType {undefined, player, enemy, projectile};

	Vehicle();
	Vehicle(float drag, float maxVelocity, float angle, float speed, VehicleType vehicleType);
	virtual ~Vehicle();

	const sf::Vector2f GetVelocity();
	const sf::IntRect GetBoundingRect();
	VehicleType GetType();

	virtual void DecrementHealth(int health);

protected:
	virtual void UpdateVelocity();  //Updates for velocity based on angle, drag, and maxspeed

	sf::Vector2f _velocity;  // -- left ++ right / -- up ++ down
	float _maxVelocity;
	float _angle;      
	float _drag;  //0-360
	float _speed;
	int _health;

private:
	VehicleType _vehicleType;
};