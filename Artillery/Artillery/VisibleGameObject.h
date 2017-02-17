#pragma once

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);

	virtual void HandleInput();
	virtual void Update(sf::Time elapsedTime);
	virtual void Draw(sf::RenderWindow & window);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(sf::Vector2f pos);

	virtual sf::Vector2f GetPosition() const;
	virtual float GetAngle() const;
	virtual int GetLayer() const;

	virtual bool IsLoaded() const;
	virtual bool IsDeleted() const;

	virtual void Delete();

protected:	
	sf::Sprite _sprite;
	//float _timer;
	float _elapsedTimeSinceStart;
	int _layer;

private:
	//std::string _filename;
	bool _isLoaded;
	bool _isDeleted;
};