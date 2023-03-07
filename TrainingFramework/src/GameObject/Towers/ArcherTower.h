#pragma once
#include "Tower.h"
#include "GameManager/ResourceManagers.h"
#include "GamePool/PoolableObject.h"

class ArcherTower : public Tower, public Poolable 
{
public:
	ArcherTower() : Tower()
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Archer Tower Front.tga");
		auto sprite = std::make_shared<Sprite2D>(model, shader, texture);
		m_sprite = sprite;
		m_range = 30000;
		m_fireRate = 2;
		m_fireCount = 0;
		m_cost = 100;
		m_towerIndex = 1;
	};
	~ArcherTower() {};
	void Reset() override {};
};