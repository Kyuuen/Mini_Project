#pragma once
#include "GamePool/GameObjectPool.h"
#include "Projectiles/Projectile.h"
class ProjectilePooling : public GameObjectPool<Projectile>, public CSingleton<ProjectilePooling> 
{
public:
	ProjectilePooling();
	~ProjectilePooling();
};

