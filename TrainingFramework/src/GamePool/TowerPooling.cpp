#include "TowerPooling.h"

TowerPooling::TowerPooling() : GameObjectPool() 
{
	m_poolLimit = 30;
	m_poolSize = 30;

	for (int i = 0; i < m_poolSize; i++)
	{
		pool.push_back(std::make_shared<ArcherTower>());
	}
}

TowerPooling::~TowerPooling() {};
