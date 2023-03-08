#include "WaveSpawner.h"
#include "ResourceManagers.h"
#include "Enemy.h"
#include "GamePool/EnemyPooling.h"

WaveSpawner::WaveSpawner()
{
    m_numWaves = 5;
    m_initialNumEnemies = 2;
    m_spawnInterval = 2.0f;
    m_spawnIntervalReduction = 1;
    m_currentWave = 0;
    m_timeSinceLastSpawn = 0.0f;
    m_numEnemiesSpawned = 0;

}

WaveSpawner::~WaveSpawner() 
{
}

void WaveSpawner::Update(GLfloat deltaTime, std::list<std::shared_ptr<Enemy>>& listEnemy) {
    m_timeSinceLastSpawn += deltaTime;

    // Check if we should spawn a new enemy
    if (m_timeSinceLastSpawn >= m_spawnInterval && m_numEnemiesSpawned < m_initialNumEnemies * (m_currentWave + 1)) {
        // Create a new enemy
        std::shared_ptr<Enemy> enemy = EnemyPooling::GetInstance()->GetFromPool();
        if (enemy != nullptr) 
        {
            enemy->GetListTarget(m_targetWaypoints);
            enemy->LockTarget();
        }
        listEnemy.push_back(enemy);

        // Reset the spawn timer
        m_timeSinceLastSpawn = 0.0f;
        m_numEnemiesSpawned++;

        // Reduce the spawn interval
        m_spawnInterval *= m_spawnIntervalReduction;
    }

    // Check if we've finished spawning this wave
    if (m_numEnemiesSpawned >= m_initialNumEnemies * (m_currentWave + 1)) {
        m_currentWave++;
        m_numEnemiesSpawned = 0;
    }
}

void WaveSpawner::GetListWaypoints(std::list<std::shared_ptr<Sprite2D>> listWaypoints)
{
    m_targetWaypoints = listWaypoints;
}