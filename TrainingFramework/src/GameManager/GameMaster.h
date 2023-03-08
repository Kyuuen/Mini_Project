#pragma once
#include "GameManager/Singleton.h"
#include "GameConfig.h"

class GameMaster : public CSingleton<GameMaster>
{
private:
	GLint m_playerHealth;
	GLint m_playerMoney;
public:
	GameMaster() 
	{
		m_playerHealth = 20;
		m_playerMoney = 200;
	};
	~GameMaster() {};
	void EnemyBreakThrough() 
	{
		m_playerHealth--;
	}
	void SpendToBuild() 
	{
		m_playerMoney -= 200;
	}
	GLint GetCurrentMoney() 
	{
		return m_playerMoney;
	}
	GLint GetCurrentHealth()
	{
		return m_playerHealth;
	}
	void GetBoundty(GLint enemyMoney)
	{
		m_playerMoney += enemyMoney;
	}
	bool GameIsOver() 
	{
		if (m_playerHealth <= 0) return true;
		else return false;
	}
};
