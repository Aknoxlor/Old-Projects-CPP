#pragma once


struct GMath
{

template <class T>
static T LimitValue(T value, T max, T min)
{
	if (value > max)
		return max;
	else if (value < min)
		return min;
	return value;
}

static sf::Vector2f CreateVector(float magnitude, float angle);
static float DotProduct(sf::Vector2f first, sf::Vector2f second);
static float TurnTowardsPoint(sf::Vector2f origin, sf::Vector2f target);
static float TurnTowardsPoint(sf::Vector2f origin, sf::Vector2f target, float startAngle, float increment);

class OriBoundingBox
{
public:
	OriBoundingBox(const sf::Vector2f center, const float width, const float height, float angle);
	~OriBoundingBox();

	bool CollisionCheck(const OriBoundingBox& other) const;

	void Draw(sf::Window& rw) const;

	private:
	sf::Vector2f _corner [4];
	sf::Vector2f _axis [2];
	float _origin[2];
	//sf::RectangleShape _renderRect;

	bool AxisOverlapCheck(const OriBoundingBox& other) const;
};
};




