#pragma once
#include "Sprite2D.h"
#include "Enemy.h"
#include "Projectile.h"
#include "GameStates/GameObjectPool.h"

class Enemy;
class Projectile;
class Tower	:	public Sprite2D
{
private:
	GLfloat m_range;
	GLfloat m_fireRate;
	GLfloat m_fireCount;
	GLint	m_cost;
public:
	Tower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat range, GLfloat fireRate, GLfloat fireCount, GLint cost, GameObjectPool* pool);
	~Tower();

	std::shared_ptr<Enemy>			m_target;
	std::shared_ptr<Projectile>		m_bullet;
	bool							m_isShooted;
	std::shared_ptr<Enemy>			m_nearestEnemy;
	GameObjectPool*					m_projectilePool;
	
	void Update(GLfloat deltaTime, std::list<std::shared_ptr<Enemy>> listEnemy);
	void UpdateTarget(std::list<std::shared_ptr<Enemy>> listEnemy);
	void Shoot();
};

