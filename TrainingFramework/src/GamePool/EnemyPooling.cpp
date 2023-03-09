#include "EnemyPooling.h"
EnemyPooling::EnemyPooling() : GameObjectPool()
{
	m_poolLimit = 50;
	m_poolSize = 50;

	for (int i = 0; i < m_poolSize; i++)
	{
		pool.push_back(std::make_shared<Enemy>());
	}
}

EnemyPooling::~EnemyPooling() {}