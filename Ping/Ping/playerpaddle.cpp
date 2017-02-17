#include "stdafx.h"
#include "playerpaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle(): _velocity(0), _maxVelocity(600.0f)
{
	Load("images/Bumper.png");
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const
{
	return _velocity;
}


void PlayerPaddle::Update(float elapsedTime)
{
	bool keyCheck(0);
	
	if(GameEngine::GetInput().IsKeyDown(sf::Key::Left))
	{
		_velocity -= 3.0f;
		keyCheck = 1;
	}

	if(GameEngine::GetInput().IsKeyDown(sf::Key::Right))
	{
		_velocity += 3.0f;
		keyCheck = 1;
	}

	if(keyCheck == 0)
	{
		if (_velocity > 3.0f)
			_velocity -= 3.0f;
		else if(_velocity <= 3.0f && _velocity >= -3.0f)
			_velocity = 0.0f;
		else if(_velocity < -3.0f)
			_velocity += 3.0f;
	}

	
	if(_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if(_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f pos = this->GetPosition();
	if(pos.x  < GetSprite().GetSize().x/2 || pos.x > (GameEngine::SCREEN_WIDTH - GetSprite().GetSize().x/2))
	{
		if (_velocity > 0)
			_velocity = -1.0;
		else if(_velocity < 0)
			_velocity = 1.0;
	}

	GetSprite().Move(_velocity * elapsedTime, 0);
}