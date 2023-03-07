#pragma once
#include "GamePool/GameObjectPool.h"
#include "Towers/ArcherTower.h"
class TowerPooling : public GameObjectPool<ArcherTower>, public CSingleton<TowerPooling>
{
public:
	TowerPooling();
	~TowerPooling();
};

