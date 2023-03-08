#pragma once
#include "GameManager/Singleton.h"
#include "GameConfig.h"
#include "Enemy.h"

class WaveSpawner : public  CSingleton<WaveSpawner>
{
public:
	WaveSpawner();
	~WaveSpawner();

	void Update(GLfloat deltaTime, std::list<std::shared_ptr<Enemy>>& listEnemy);
	void GetListWaypoints(std::list<std::shared_ptr<Sprite2D>> listWaypoints);
	std::list<std::shared_ptr<Enemy>> GetEnemies() const {
		return m_listEnemies;
	}
	std::list<std::shared_ptr<Sprite2D>> m_targetWaypoints;

private:
	GLint m_numWaves;
	GLint m_initialNumEnemies;
	GLfloat m_spawnInterval;
	GLfloat m_spawnIntervalReduction;
	GLfloat m_timeSinceLastSpawn;
	GLint m_currentWave;
	GLint m_numEnemiesSpawned;
	std::list<std::shared_ptr<Enemy>> m_listEnemies;
	GLfloat timeBetweenWave = 5.f;
};

