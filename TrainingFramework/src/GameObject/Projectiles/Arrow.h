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
		auto texture = ResourceManagers::GetInstance()->GetTexture("arrow.tga");
		m_pModel = model;
		m_pShader = shader;
		m_pTexture = texture;
		auto sprite = std::make_shared<Sprite2D>(model, shader, texture);
		m_sprite = sprite;
		m_speed = 70;
		m_damage = 10;
	};
	~Arrow() {};
	void Reset() override {};
};

