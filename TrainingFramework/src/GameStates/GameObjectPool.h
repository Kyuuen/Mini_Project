#pragma once
#include "GameConfig.h"
#include "Projectile.h"
class GameObjectPool
{
private:
	std::list<std::shared_ptr<Projectile>*> m_gameObjectPool;
	int m_poolSize;
public:
	GameObjectPool(int size);
	~GameObjectPool();
	std::shared_ptr<Projectile>* GetGameObject();
	void ReturnGameObject(std::shared_ptr<Projectile>* obj);
};

