#pragma once
#include "Projectile.h"
#include "GameManager/ResourceManagers.h"
#include "GamePool/PoolableObject.h"
class Arrow : public Projectile, public Poolable
{
public:
	Arrow() : Projectile()
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("stone.tga");
		m_pModel = model;
		m_pShader = shader;
		m_pTexture = texture;
		m_speed = 300;
		m_damage = 10;
		SetSize(20, 20);
		//Set2DRotation();
	};
	~Arrow() {};
	void Reset() override 
	{ 
		this->DisableObject();
		Set2DPosition(0, 0);
	};
};

