#pragma once
#include "visiblegameobject.h"
//#include "stdafx.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Add(std::string name, VisibleGameObject* object);
	void Remove(std::string name);
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;

	void DrawAll(sf::RenderWindow& renderWindow);

	void UpdateAll();

private:
	std::map<std::string, VisibleGameObject*> _objects;

	struct ObjectDeallocator
	{
		void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};