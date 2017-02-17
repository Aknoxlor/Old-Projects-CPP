#include "stdafx.h"
#include "Projectiles.h"
#include "Game.h"
#include "Players.h"

Player_1::Player_1(sf::Vector2f position, float angle):
	AbstractPlayer(125.0f, 0.1f, 100)
{
	Load("images/Cannon A.png");
	assert(IsLoaded());

	_angle = angle;
	_speed = 0;

	sf::IntRect rect(6, 38, 49, 20);
	_sprite.setTextureRect(rect);
	_sprite.setOrigin(float(rect.width) / 2, float(rect.height) / 2 );

	_sprite.setPosition(position);
	_sprite.setRotation(angle);

	_turret.Sync(this);
}

Player_1::~Player_1()
{
}



void Player_1::Draw(sf::RenderWindow& rw)
{	
	sf::Vector2f temp = _sprite.getPosition();
	_healthBar.SetPosition(temp.x + 25, temp.y - 25);

	//GetBoundingBox().Draw(rw);
	VisibleGameObject::Draw(rw);
	_turret.Draw(rw);
	_healthBar.Draw(rw);
}

void Player_1::Update(sf::Time elapsedTime)
{
	AbstractPlayer::HandleInput();
	_turret.HandleInput();

	AbstractPlayer::Update(elapsedTime);
	_turret.Update(elapsedTime);
}



Player_1::Turret_1::Turret_1()
	:AbstractTurret(0.2f)
{
	Load("images/Cannon A.png");
	assert(IsLoaded());

	sf::IntRect rect2(7, 3, 18, 27);
	_sprite.setTextureRect(rect2);
	_sprite.setOrigin(float(rect2.width) / 2, float(rect2.height) / 4*3);
}

inline VehicleObject* Player_1::Turret_1::NewProjectile(const VehicleObject &origin)
{
	return new Projectile(*this);
}

	/*
	if(pos.x  < _sprite.getScale().x/2)
	{
		_sprite.SetPosition(pos.x + 1,pos.y);
		_velocity.x = 0;
	}
	else if(pos.x > (GameEngine::SCREEN_WIDTH - _sprite.getScale().x/2))
	{
		_sprite.SetPosition(pos.x - 1,pos.y);
		_velocity.x = 0;
	}

	if(pos.y  < _sprite.getScale().y/2)
	{
		_sprite.SetPosition(pos.x, pos.y + 1);
		_velocity.y = 0;
	}
	else if(pos.y > (GameEngine::SCREEN_HEIGHT - _sprite.getScale().y/2))
	{
		_sprite.SetPosition(pos.x, pos.y - 1);
		_velocity.y = 0;
	}
	*/