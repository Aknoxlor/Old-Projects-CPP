#include "stdafx.h"
#include "Game.h"
#include "AbstractEnemy.h"

void AbstractEnemy::Update(sf::Time elapsedTime)
{
	_elapsedTime = elapsedTime.asSeconds();
	_elapsedTimeSinceStart += _elapsedTime;
	SeekTarget();
	_sprite.move(_velocity.x * _elapsedTime, _velocity.y * _elapsedTime);
	_sprite.setRotation(-_angle);
	CollisionDetection();
}

void AbstractEnemy::Draw(sf::RenderWindow& rw)
{
	sf::Vector2f temp = _sprite.getPosition();
	_healthBar.SetPosition(temp.x + 15, temp.y - 15);

	//GetBoundingBox().Draw(rw);
	VisibleGameObject::Draw(rw);
	_healthBar.Draw(rw);
}


void AbstractEnemy::Damage(unsigned int damageAmount)
{
	_health -= damageAmount;

	if(_health <= 0)
		Delete();
	else
		_healthBar.SetScale(float(_health) / float(_maxHealth));
}

void AbstractEnemy::Repair(unsigned int repairAmount)
{
	if((_health + repairAmount) <= _maxHealth)
	_health = _health + repairAmount;
	else
	_health = _maxHealth;

	_healthBar.SetScale(float(_health) / float(_maxHealth));
}


///// Protected /////


AbstractEnemy::AbstractEnemy(const float maxVelocity, const float drag, const int maxHealth)
	: VehicleObject(maxVelocity, drag, maxHealth, 45.0f, enemy)
{
	currentTarget = dynamic_cast<VehicleObject*>(GameEngine::GetObjectManager().Get("Cannon"));
	assert(currentTarget != NULL);
	_layer = 4;
}

AbstractEnemy::~AbstractEnemy()
{

}



void AbstractEnemy::SeekTarget()
{
	sf::Vector2f pos = _sprite.getPosition();
	sf::Vector2f targetPos = currentTarget->GetPosition();

	_angle = GMath::TurnTowardsPoint(pos, targetPos, _angle, (_turnSpeed * _elapsedTime));
	
	sf::Vector2f temp = sf::Vector2f(targetPos.x - pos.x, targetPos.y - pos.y);
	float distance = sqrt(temp.x*temp.x + temp.y*temp.y);
	_speed += 0.5f;

	if (_speed > 0)
		_speed -= _drag;  

	if (_speed > _maxVelocity)
		_speed = _maxVelocity;

	_velocity = GMath::CreateVector(_speed, _angle);
}


void AbstractEnemy::CollisionDetection()
{
	VehicleObject* vehicle = dynamic_cast<VehicleObject*> (GameEngine::GetObjectManager().Get("Cannon"));
	if (vehicle->GetBoundingBox().CollisionCheck(GetBoundingBox())) //REALLY BAD collision detection
	{
				Delete();
				vehicle->Damage(10);
				return;
	}
}