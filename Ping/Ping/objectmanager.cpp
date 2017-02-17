#include "stdafx.h"
#include "objectmanager.h"
#include "Game.h"


ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	std::for_each(_objects.begin(),_objects.end(),ObjectDeallocator());
}

void ObjectManager::Add(std::string name, VisibleGameObject *object)
{
	_objects.insert(std::pair<std::string, VisibleGameObject*>(name,object));
}

void ObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _objects.find(name);
	if (results != _objects.end())
	{
		delete results->second;
		_objects.erase(results);
	}
}

VisibleGameObject* ObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _objects.find(name);
	if (results == _objects.end())
		return NULL;
	return results->second;
}

int ObjectManager::GetObjectCount() const
{
	return _objects.size();
}

void ObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _objects.begin();
	while(itr != _objects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void ObjectManager::UpdateAll()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _objects.begin();

	float timeDelta = GameEngine::GetWindow().GetFrameTime();

	while(itr != _objects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}
}

