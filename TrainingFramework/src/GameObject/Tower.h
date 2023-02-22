#pragma once
#include "Sprite2D.h"
#include "Enemy.h"
#include "Projectile.h"

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
	Tower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat range, GLfloat fireRate, GLfloat fireCount, GLint cost);
	~Tower();

	std::shared_ptr<Enemy> m_target;
	std::shared_ptr<Projectile>	m_bullet;
	std::list<std::shared_ptr<Enemy>>	m_listEnemies;
	
	void Update(GLfloat deltaTime) override;
	void UpdateTarget(std::list<std::shared_ptr<Enemy>> listEnemy);
	void Shoot(std::shared_ptr<Projectile> bullet);
};

