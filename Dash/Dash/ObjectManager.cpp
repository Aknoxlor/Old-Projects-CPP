#include "stdafx.h"
#include "ObjectManager.h"
#include "Game.h"


ObjectManager::ObjectManager()
{
	_dynamicObjects.reserve(10);
}

ObjectManager::~ObjectManager()
{
	std::for_each(_objects.begin(),_objects.end(),ObjectDeallocator());
	std::for_each(_dynamicObjects.begin(),_dynamicObjects.end(),DynamicObjectDeallocator());
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

int ObjectManager::GetObjectCount() const
{
	return _objects.size();
}

VisibleGameObject* ObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _objects.find(name);
	if (results == _objects.end())
		return NULL;
	return results->second;
}



void ObjectManager::AddDynamic(VisibleGameObject *object)
{
	_dynamicQueue.push_back(object);
}

int ObjectManager::GetDynamicCount() const
{
	return _dynamicObjects.size();
}

VisibleGameObject* ObjectManager::GetDynamic(unsigned int iterator) const
{
	std::vector<VisibleGameObject*>::const_iterator dynItr = _dynamicObjects.begin() + iterator;
	if (dynItr == _dynamicObjects.end() || *dynItr == NULL)
		return NULL;
	else
		return (*dynItr);
}



void ObjectManager::DrawAll(sf::RenderWindow& rw) const
{
	int zayer(10);

	std::map<std::string, VisibleGameObject*>::const_iterator itr = _objects.begin();
	while(itr != _objects.end())
	{
		//if(rw.getView().getViewport().contains(itr->second->GetPosition().x, itr->second->GetPosition().y))
			itr->second->Draw(rw);
		itr++;
	}

	std::vector<VisibleGameObject*>::const_iterator iter = _dynamicObjects.begin();
	while(iter != _dynamicObjects.end())
	{
		if(*iter != NULL)
		{
			(*iter)->SetPosition(zayer, ((*iter)->GetLayer() * 50));
			(*iter)->Draw(rw);
		}
		zayer += 50;
		iter++;
	}
}

void ObjectManager::UpdateAll() const
{
	sf::Time timeDelta = GameEngine::_frameClock.restart();

	std::map<std::string, VisibleGameObject*>::const_iterator itr = _objects.begin();
	while(itr != _objects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}

	std::vector<VisibleGameObject*>::const_iterator dynItr = _dynamicObjects.begin();
	while(dynItr != _dynamicObjects.end())
	{
		if(*dynItr != NULL)
			(*dynItr)->Update(timeDelta);
		dynItr++;
	}

}



void ObjectManager::MemoryManage()
{
	if(_dynamicQueue.size() != 0)
	{
		_dynamicObjects.reserve(_dynamicQueue.size());
		std::vector<VisibleGameObject*>::const_iterator iter = _dynamicQueue.begin();
		while(iter != _dynamicQueue.end())
		{
			DynamicInsert(*iter);
			iter++;
		}
		_dynamicQueue.clear();
	}

	std::vector<VisibleGameObject*>::iterator iter = _dynamicObjects.begin();
	while(iter != _dynamicObjects.end())
	{
		if (*iter != NULL && (*iter)->IsDeleted())
		{
			delete (*iter);
			*iter = 0;
			//iter = _dynamicObjects.erase(iter);
			iter++; //temp
		}
		else
			iter++;
	}
}



void ObjectManager::DynamicInsert(VisibleGameObject* object)
{
	if(_dynamicObjects.size() == 0)
	{
		_dynamicObjects.push_back(object);
		return;
	}

	std::vector<VisibleGameObject*>::iterator iter = _dynamicObjects.begin();
	while(iter != _dynamicObjects.end()) //Iterate forward to end
	{
		if(*iter != NULL && (object->GetLayer() < (*(*iter)).GetLayer())) //Check it see if iterator layer is bigger than object layer
		{
			while(iter != _dynamicObjects.begin()) //Iterate backwords
			{
				iter--;
				if(*iter == NULL || (*(*iter)).IsDeleted()) //If free space, insert object in space
				{
					delete (*iter);
					(*iter) = object;
					return;
				}
				if(object->GetLayer() != (*(*iter)).GetLayer()) //If at beginning of valid layer range, insert object
				{
					_dynamicObjects.insert((iter + 1), object);
					return;
				}
			}
			_dynamicObjects.insert((iter), object); //If at beginning of vector, insert object
			return;
		}
		iter++;
	}

	if(*(iter - 1) == NULL || (*(*(iter - 1))).IsDeleted()) //If all layers are smaller than object, put at the end
	{
		delete (*(iter - 1));
		(*(iter - 1)) = object;
	}
	else
		_dynamicObjects.push_back(object);
}