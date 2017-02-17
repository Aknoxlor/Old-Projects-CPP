#pragma once
#include "VisibleGameObject.h"

class ScalingBar :
	public VisibleGameObject
{
public:
	ScalingBar();
	~ScalingBar();

	void Draw(sf::RenderWindow& rw);

	void SetScale(float percentage);

private:
	float _scale;

	sf::RectangleShape _dynamicBar;
};