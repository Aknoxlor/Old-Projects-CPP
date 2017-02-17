#pragma once
#include "VehicleObject.h"

class AbstractTurret:
	public VehicleObject
{
public:
	void HandleInput();
	void Update(sf::Time elpasedTime);
	void Sync(const VehicleObject *mount);

protected:
	AbstractTurret(const VehicleObject *mount, const float fireRate);
	AbstractTurret(const float fireRate);
	virtual ~AbstractTurret();

	const VehicleObject* _vehicleMount;
	const float _fireRate;
	float _mouseAngle;

	bool _isFiring;

	virtual VehicleObject* NewProjectile(const VehicleObject &origin) = 0;
};