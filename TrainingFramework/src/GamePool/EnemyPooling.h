#pragma once
#include "GamePool/GameObjectPool.h"
#include "Enemy.h"
class EnemyPooling : public GameObjectPool<Enemy>, public CSingleton<EnemyPooling>
{
public:
	EnemyPooling();
	~EnemyPooling();
};

