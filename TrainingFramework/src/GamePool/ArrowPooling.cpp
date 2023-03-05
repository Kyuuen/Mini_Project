#include "ArrowPooling.h"

ArrowPooling::ArrowPooling() : GameObjectPool()
{
	m_poolLimit = 10;
	m_poolSize = 10;

	for (int i = 0; i < m_poolSize; i++)
	{
		pool.push_back(std::make_shared<Arrow>());
	}
}

ArrowPooling::~ArrowPooling(){}