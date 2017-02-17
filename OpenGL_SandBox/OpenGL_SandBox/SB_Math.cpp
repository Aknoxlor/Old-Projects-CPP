#include "stdafx.h"
#include "SB_Math.h"

sf::Vector2f GMath::CreateVector(float magnitude, float angle)
{
	sf::Vector2f vector;
	float radAngle = (angle * 3.14159265 / 180);
	
	vector.y = sin(-radAngle) * magnitude;
	vector.x = cos(-radAngle) * magnitude;

	return vector;
}

float GMath::DotProduct(sf::Vector2f first, sf::Vector2f second)
{
	return (first.x * second.x - first.y * second.y);
}

float GMath::TurnTowardsPoint(sf::Vector2f origin, sf::Vector2f target)
{
	float finalAngle = 0;
	sf::Vector2f unit(0,0);

	unit.x = (target.x - origin.x);
	unit.y = (target.y - origin.y);

	finalAngle = (std::atan2(unit.x, unit.y) * 180 / 3.14159265);

	return finalAngle;
}

float GMath::TurnTowardsPoint(sf::Vector2f origin, sf::Vector2f target, float startAngle, float increment)
{
	float finalAngle = startAngle;

	//Converts target and origin into unit vector
	sf::Vector2f unit(0,0);
	unit.x = (target.x - origin.x);	
	unit.y = (target.y - origin.y);	
	float length = sqrt(unit.x*unit.x + unit.y*unit.y);	
	unit.x /= length;
	unit.y /= length;

	//Converts startAngle into direction vector
	sf::Vector2f dir(0,0);	
	dir.x = sin((startAngle - 90) * 3.14159265 / 180);
	dir.y = cos((startAngle - 90) * 3.14159265 / 180);

	//Fun with dot products
	float dotProd = (dir.x * unit.y - dir.y * unit.x);
	if (dotProd > 0.1f)
		finalAngle += increment;
	else if (dotProd < -0.1f)
		finalAngle -= increment;

	return finalAngle;
}



GMath::OriBoundingBox::OriBoundingBox(const sf::Vector2f center, const float width, const float height, float angle)
{
	angle = -angle * (3.14159265 / 180);

	sf::Vector2f angleVectorX( cos(angle), sin(angle));
	sf::Vector2f angleVectorY(-sin(angle), cos(angle));
	
	angleVectorX *= width / 2;
	angleVectorY *= height / 2;

	_corner[0] = center - angleVectorX - angleVectorY;
	_corner[1] = center + angleVectorX - angleVectorY;
	_corner[2] = center + angleVectorX + angleVectorY;
	_corner[3] = center - angleVectorX + angleVectorY;

	_axis[0] = _corner[1] - _corner[0];
	_axis[1] = _corner[3] - _corner[0];

	for(int iii(0); iii < 2; ++iii)
	{
		_axis[iii] /= ((_axis[iii].x * _axis[iii].x) + (_axis[iii].y * _axis[iii].y));
		_origin[iii] = DotProduct(_corner[0], _axis[iii]);
	}

	/*
	_renderRect.setSize(sf::Vector2f(width, height));
	_renderRect.setOrigin(width/2, height/2);
	_renderRect.setPosition(center);
	_renderRect.setRotation(angle * (180 / 3.14159265));
	_renderRect.setFillColor(sf::Color(100, 100, 100));
	*/
}

GMath::OriBoundingBox::~OriBoundingBox()
{

}

bool GMath::OriBoundingBox::CollisionCheck(const OriBoundingBox& other) const
{
	return (AxisOverlapCheck(other) && other.AxisOverlapCheck(*this));
}

void GMath::OriBoundingBox::Draw(sf::Window& rw) const
{
	//rw.draw(_renderRect);
}

bool GMath::OriBoundingBox::AxisOverlapCheck(const OriBoundingBox& other) const
{
	for (int iii(0); iii < 2; ++iii)
	{
		float temp = DotProduct(other._corner[0],_axis[iii]);

		//Find the extent of the second box's axis being tested
		float tMin = temp;
		float tMax = temp;
		for (int jjj(1); jjj < 4; ++jjj)
		{
			temp = DotProduct(other._corner[jjj],_axis[iii]);
			if (temp < tMin)
				tMin = temp;
			else if (temp > tMax)
				tMax = temp;
		}

		// Test for overlap between the two boxs' axis
		if ((tMin > (1 + _origin[iii])) || (tMax < _origin[iii]))
			return false;
	}
	return true;
}

