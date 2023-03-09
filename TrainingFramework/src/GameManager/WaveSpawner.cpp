#include "WaveSpawner.h"
#include "ResourceManagers.h"
#include "Enemy.h"
#include "GamePool/EnemyPooling.h"

WaveSpawner::WaveSpawner()
{
    m_waveIndex = 1;
    m_waveCountDown = 2;
    m_enemySpawned = 0;
    m_timeBetweenWave = 7.0f;
    m_spawnRate = 1.2f;
    m_spawnCountDown = 1.0f / m_spawnRate;
    m_isPlayed = false;
}

WaveSpawner::~WaveSpawner() 
{
}

void WaveSpawner::Update(GLfloat deltaTime, std::list<std::shared_ptr<Enemy>>& listEnemy) 
{
    m_waveCountDown -= deltaTime;
    // Check if the next wave incomming?
    if (m_waveCountDown <= 0) 
    {
        if(!m_isPlayed)
        {
            ResourceManagers::GetInstance()->PlaySound("newgame.wav");
            m_isPlayed = true;
        }

        m_spawnCountDown -= deltaTime;
        //Check if we have wait enough to spawn 1 more
        if (m_spawnCountDown <= 0) 
        {
            if (m_enemySpawned < m_waveIndex)
            {
                // Create a new enemy
                std::shared_ptr<Enemy> enemy = EnemyPooling::GetInstance()->GetFromPool();
                if (enemy != nullptr)
                {
                    enemy->GetListTarget(m_targetWaypoints);
                    enemy->LockTarget();
                }
                listEnemy.push_back(enemy);
                m_enemySpawned++;
            }
            else
            {
                m_waveCountDown = m_timeBetweenWave;
                m_waveIndex++;
                m_enemySpawned = 0;
            }
            m_spawnCountDown = 1.f / m_spawnRate;
        }
    }
    else
        m_isPlayed = false;
}

void WaveSpawner::GetListWaypoints(std::list<std::shared_ptr<Sprite2D>> listWaypoints)
{
    m_targetWaypoints = listWaypoints;
}

GLfloat WaveSpawner::GetWaveCountDown()
{
    return m_waveCountDown;
}