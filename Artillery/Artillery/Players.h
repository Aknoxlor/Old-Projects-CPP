#pragma once
#include "AbstractPlayer.h"
#include "AbstractTurret.h"

class Turret_1 :
	public AbstractTurret
{
public:
	Turret_1();
	VehicleObject* NewProjectile(const VehicleObject &origin);
};

class Player_1 :
	public AbstractPlayer
{
public:
	Player_1(sf::Vector2f position, float angle);
	~Player_1();

	void Update(sf::Time elapsedTime);
	void Draw(sf::RenderWindow& rw);

private:

	class Turret_1 :
	public AbstractTurret
{
	public:
	Turret_1();
	VehicleObject* NewProjectile(const VehicleObject &origin);
};
	Turret_1 _turret;
};

