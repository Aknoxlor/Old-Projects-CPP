#pragma once
#include "VisibleGameObject.h"

class VehicleObject :
	public VisibleGameObject
{
public:
	enum VehicleType {undefined, player, enemy, projectile, turret};

	float GetAngle() const;
	sf::Vector2f GetVelocity() const;
	VehicleType GetType() const;
	GMath::OriBoundingBox GetBoundingBox() const;

	virtual void Damage(unsigned int damageAmount);
	virtual void Repair(unsigned int repairAmount);

protected:
	VehicleObject();
	VehicleObject(const float maxVelocity, const float drag, const int maxHealth, const float turnSpeed, const VehicleType vehicleType);
	virtual ~VehicleObject();

	const float _maxVelocity;
	const float _drag;
	const float _turnSpeed;
	const int _maxHealth;


	sf::Vector2f _velocity;  // -- left ++ right / -- up ++ down
	float _elapsedTime;
	float _angle;     
	float _speed;
	int _health;

private:
	const VehicleType _vehicleType;
};