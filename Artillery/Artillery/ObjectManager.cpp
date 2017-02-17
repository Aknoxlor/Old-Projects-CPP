#include "stdafx.h"
#include "Game.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	_dynamicObjects.reserve(10);
}

ObjectManager::~ObjectManager()
{
	ClearAll();
}



void ObjectManager::Add(VisibleGameObject *object)
{
	_dynamicQueue.push_back(object);
}

void ObjectManager::AddTagged(std::string nameTag, VisibleGameObject *object)
{
	_objectTags.insert(std::pair<std::string, VisibleGameObject*>(nameTag, object));
	_dynamicQueue.push_back(object);
}



void ObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _objectTags.find(name);
	if (results != _objectTags.end())
	{
		results->second->Delete();
		_objectTags.erase(results);
	}
}



VisibleGameObject* ObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _objectTags.find(name);
	if (results == _objectTags.cend())
		return NULL;
	return results->second;
}

VisibleGameObject* ObjectManager::Get(unsigned int iterator) const
{
	std::vector<VisibleGameObject*>::const_iterator dynItr = _dynamicObjects.cbegin() + iterator;
	if (dynItr == _dynamicObjects.cend() || *dynItr == NULL)
		return NULL;
	else
		return (*dynItr);
}

int ObjectManager::GetObjectCount() const
{
	return _dynamicObjects.size();
}



void ObjectManager::IterateAll(std::function<void (VisibleGameObject*)> func)
{
	std::for_each(_dynamicObjects.begin(), _dynamicObjects.end(), func);
}



void ObjectManager::MemoryManage()
{
	if(_dynamicQueue.size() != 0)
	{
		_dynamicObjects.reserve(_dynamicQueue.size());
		std::for_each(_dynamicQueue.begin(),_dynamicQueue.end(),[&](VisibleGameObject* &object)
		{
			SortedInsert(object);
		});
		_dynamicQueue.clear();
	}

	std::vector<VisibleGameObject*>::iterator iter = _dynamicObjects.begin();
	while(iter != _dynamicObjects.end())
	{
		if (*iter != NULL && (*iter)->IsDeleted())
		{
			delete (*iter); //SHOULD just delete objects and leave pointers open to assignment
			*iter = NULL;
			iter++; 
		}
		else
			iter++;
	}
}



void ObjectManager::SortedInsert(VisibleGameObject* object)
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

	if(*(iter - 1) == NULL || (*(*(iter - 1))).IsDeleted()) //If all layers are smaller than object layer, put at the end
	{
		delete (*(iter - 1));
		(*(iter - 1)) = object;
	}
	else
		_dynamicObjects.push_back(object);
}

void ObjectManager::ClearAll()
{
	std::for_each(_dynamicObjects.begin(),_dynamicObjects.end(),[](VisibleGameObject* & v)
	{
		delete v;
	});

	std::for_each(_dynamicQueue.begin(),_dynamicQueue.end(),[](VisibleGameObject* & q)
	{
		delete q;
	});

	_objectTags.clear();
	_dynamicObjects.clear();
	_dynamicQueue.clear();
}