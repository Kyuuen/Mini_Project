#pragma once
#include "Sprite2D.h"
#include "Enemy.h"
#include "Projectiles/Arrow.h"
#include "GamePool/ArrowPooling.h"
#include "ResourceManagers.h"
#include <iostream>
class Enemy;
class Tower	:	public Sprite2D, public std::enable_shared_from_this<Tower>
{
private:
	
protected:
	std::shared_ptr<Sprite2D> m_sprite;
	GLfloat m_range;
	GLfloat m_fireRate;
	GLfloat m_fireCount;
	GLint	m_cost;
public:
	Tower();
	Tower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat range, GLfloat fireRate, GLfloat fireCount, GLint cost);
	~Tower();

	std::shared_ptr<Enemy>			m_target;
	std::shared_ptr<Projectile>		m_bullet;
	bool							m_isShooted;
	std::shared_ptr<Enemy>			m_nearestEnemy;
	GLint							m_towerIndex;
	
	void Update(GLfloat deltaTime, std::list<std::shared_ptr<Enemy>> listEnemy);
	void UpdateTarget(std::list<std::shared_ptr<Enemy>> listEnemy);
	std::shared_ptr<Arrow>		ShootArrow();
};

