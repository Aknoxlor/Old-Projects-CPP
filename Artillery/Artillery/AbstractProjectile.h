#pragma once
#include "VehicleObject.h"
//#include "ScalingBar.h"

class AbstractProjectile :
	public VehicleObject
{
public:
	virtual void Update(sf::Time elapsedTime);
	
protected:
	AbstractProjectile(const VehicleObject &origin, const float maxVelocity, const int maxRange, const float drag = 0, const int maxHealth = 10);
	virtual ~AbstractProjectile();

	void CollisionDetection();

	VehicleType _target;
	//ScalingBar _healthBar;
	float _distanceTraveled;
	const int _maxRange;
};