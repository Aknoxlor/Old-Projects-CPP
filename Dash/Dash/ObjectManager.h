#pragma once
#include "VisibleGameObject.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Add(std::string name, VisibleGameObject* object);
	void Remove(std::string name);
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;

	void AddDynamic(VisibleGameObject* object);
	int GetDynamicCount() const;
	VisibleGameObject* GetDynamic(unsigned int iterator) const;

	void HandleInputAll() const;
	void DrawAll(sf::RenderWindow& renderWindow) const;
	void UpdateAll() const;

	void MemoryManage();

private:
	std::map<std::string, VisibleGameObject*> _objects;
	std::vector<VisibleGameObject*> _dynamicObjects;
	std::vector<VisibleGameObject*> _dynamicQueue;

	void DynamicInsert(VisibleGameObject* object);

	struct ObjectDeallocator
	{
		void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};

	struct DynamicObjectDeallocator
	{
		void operator()(VisibleGameObject* & v) const
		{
			delete v;
		}
	};
};