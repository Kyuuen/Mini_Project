#pragma once
#include "GamePool/GameObjectPool.h"
#include "Projectiles/Arrow.h"
class ArrowPooling : public GameObjectPool<Arrow>, public CSingleton<Arrow>
{
public:
	ArrowPooling();
	~ArrowPooling();
};

