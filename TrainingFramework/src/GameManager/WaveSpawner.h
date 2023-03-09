#pragma once
#include "GameManager/Singleton.h"
#include "GameConfig.h"
#include "Enemy.h"
#include "GameManager/ResourceManagers.h"

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
	GLfloat GetWaveCountDown();
private:
	std::list<std::shared_ptr<Enemy>> m_listEnemies;
	GLfloat m_timeBetweenWave;
	GLint	m_waveIndex;
	GLfloat	m_waveCountDown;
	GLfloat m_spawnCountDown;
	GLfloat m_spawnRate;
	GLint	m_enemySpawned;
	GLboolean m_isPlayed;
};

