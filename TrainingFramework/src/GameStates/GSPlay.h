#pragma once
#include "GameStateBase.h"
#include "Towers/ArcherTower.h"
#include "GamePool/TowerPooling.h"

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
	void	BuildTower();

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int		m_KeyPress;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<Sprite2D>>	m_listWaypoint;
	std::list<std::shared_ptr<Enemy>>		m_listEnemy;
	std::list<std::shared_ptr<ArcherTower>>		m_listTower;
	std::list<std::shared_ptr<Arrow>>		m_listArrow;
};

