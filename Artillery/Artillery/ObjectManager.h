#pragma once
#include "VisibleGameObject.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();


	void Add(VisibleGameObject* object);
	void AddTagged(std::string name, VisibleGameObject* object);
	
	void Remove(std::string name);

	VisibleGameObject* Get(std::string name) const;
	VisibleGameObject* Get(unsigned int iterator) const;
	int GetObjectCount() const;

	void IterateAll(std::function<void (VisibleGameObject*)> func);
	void ClearAll();

	void MemoryManage();

private:
	std::map<std::string, VisibleGameObject*> _objectTags;
	std::vector<VisibleGameObject*> _dynamicObjects;
	std::vector<VisibleGameObject*> _dynamicQueue;

	void SortedInsert(VisibleGameObject* object);
};