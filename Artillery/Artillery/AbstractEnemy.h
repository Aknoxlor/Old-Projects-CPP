#pragma once
#include "VehicleObject.h"
#include "ScalingBar.h"

class AbstractEnemy :
	public VehicleObject
{
public:
	virtual void Update(sf::Time elapsedTime);
	virtual void Draw(sf::RenderWindow& renderWindow);

	virtual void Damage(unsigned int damageAmount);
	virtual void Repair(unsigned int repairAmount);

protected:
	AbstractEnemy(const float maxVelocity, const float drag, const int maxHealth);
	virtual ~AbstractEnemy();

	void SeekTarget();

	ScalingBar _healthBar;
	VehicleObject* currentTarget;

private:
	void CollisionDetection();
};