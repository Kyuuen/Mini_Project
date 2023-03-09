#pragma once
#include "GameStateBase.h"
#include "Towers/ArcherTower.h"
#include "GamePool/TowerPooling.h"
#include "GameManager/WaveSpawner.h"
#include "GameManager/GameMaster.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;
class Enemy;
class Tower;
class Projectile;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;
	void	GameOver();
	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int		m_KeyPress;

private:
	GLboolean m_isOver;
	GLboolean m_isPause;
	GLboolean m_pauseToDraw;
	GLboolean m_isPlayed;
	GLboolean m_Overing;
	std::shared_ptr<Sprite2D>	m_gameOver;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_money;
	std::shared_ptr<Text>		m_health;
	std::shared_ptr<Text>		m_pauseText;
	std::shared_ptr<Text>		m_waveCountDown;
	std::shared_ptr<Text>		m_enemiesKilled;
	std::shared_ptr<Text>		m_gameOverText;
	std::list<std::shared_ptr<GameButton>>	m_exitButton;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<Sprite2D>>	m_listWaypoint;
	std::list<std::shared_ptr<Enemy>>		m_listEnemy;
	std::list<std::shared_ptr<ArcherTower>>		m_listTower;
	std::list<std::shared_ptr<Arrow>>		m_listArrow;
	std::list<std::shared_ptr<GameButton>>	m_listNode;
};

