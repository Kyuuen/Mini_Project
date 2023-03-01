#include "WaveSpawner.h"
#include "ResourceManagers.h"
#include "Enemy.h"

WaveSpawner::WaveSpawner(int numWaves, int initialNumEnemies, float spawnInterval, float spawnIntervalReduction, std::list<std::shared_ptr<Sprite2D>> targetPositions) :
    m_numWaves(numWaves),
    m_initialNumEnemies(initialNumEnemies),
    m_spawnInterval(spawnInterval),
    m_spawnIntervalReduction(spawnIntervalReduction),
    m_targetWaypoints(targetPositions),
    m_currentWave(0),
    m_timeSinceLastSpawn(0.0f),
    m_numEnemiesSpawned(0)
{
}

WaveSpawner::~WaveSpawner() 
{
}

void WaveSpawner::Update(GLfloat deltaTime) {
    m_timeSinceLastSpawn += deltaTime;

    // Check if we should spawn a new enemy
    if (m_timeSinceLastSpawn >= m_spawnInterval && m_numEnemiesSpawned < m_initialNumEnemies * (m_currentWave + 1)) {
        // Create a new enemy
        auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
        auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
        auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy2Idle.tga");
        std::shared_ptr<Enemy>	enemy = std::make_shared<Enemy>(model, shader, texture, 30, 120, m_targetWaypoints);
        enemy->LockTarget();
        enemy->Set2DPosition(200, 100);
        enemy->SetSize(320, 320);
        m_listEnemies.push_back(enemy);

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

