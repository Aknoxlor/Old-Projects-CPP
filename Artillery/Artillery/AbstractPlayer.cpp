#include "stdafx.h"
#include "Game.h"
#include "AbstractPlayer.h"

void AbstractPlayer::HandleInput()
{
	_inputAngle = _angle;
	_inputSpeed = _speed;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_inputAngle -= _turnSpeed;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_inputAngle += _turnSpeed;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_inputSpeed += 0.6f;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_inputSpeed -= 0.3f;
}

void AbstractPlayer::Update(sf::Time elapsedTime)
{
	_elapsedTime = elapsedTime.asSeconds();
	_elapsedTimeSinceStart += _elapsedTime;

	_angle += (_inputAngle - _angle) * _elapsedTime;
	_speed = _inputSpeed;

	if(_speed == GMath::LimitValue(_speed, _drag, -_drag))
		_speed = 0;
	else if (_speed > 0)
		_speed -= _drag;  
	else if(_speed < 0)
		_speed += _drag;

	_speed = GMath::LimitValue(_speed, _maxVelocity, (-_maxVelocity / 2));
	_velocity = GMath::CreateVector(_speed, _angle);

	_sprite.move(_velocity.x * _elapsedTime, _velocity.y * _elapsedTime);
	_sprite.setRotation(-_angle);
}



void AbstractPlayer::Damage(unsigned int damageAmount)
{
	_health -= damageAmount;

	if(_health <= 0)
	{
		_healthBar.SetScale(1.0f); //Death temporarily disabled for debugging
		_health = _maxHealth;
	}
	else
		_healthBar.SetScale(float(_health) / float(_maxHealth));
}

void AbstractPlayer::Repair(unsigned int repairAmount)
{
	_health += repairAmount;
	_healthBar.SetScale(float(_health) / float(_maxHealth));
	return;
}

///// Protected /////

AbstractPlayer::AbstractPlayer(const float maxVelocity, const float drag, const int maxHealth)
	: VehicleObject(maxVelocity, drag, maxHealth, 60.0f, player)
{
	_layer = 3;
}

AbstractPlayer::~AbstractPlayer()
{

}
