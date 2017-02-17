#pragma once
#include "VehicleObject.h"
#include "ScalingBar.h"

class AbstractPlayer :
	public VehicleObject
{
public:
	virtual void HandleInput();
	virtual void Update(sf::Time elapsedTime);
	//virtual void Draw(sf::RenderWindow & window);

	virtual void Damage(unsigned int damageAmount);
	virtual void Repair(unsigned int repairAmount);
	
protected:
	AbstractPlayer(const float maxVelocity, const float drag, const int maxHealth);
	virtual ~AbstractPlayer();

	float _inputAngle;
	float _inputSpeed;
	ScalingBar _healthBar;
};