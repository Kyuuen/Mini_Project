#pragma once
#include "Sprite2D.h"
#include "Enemy.h"

class Enemy;
class Projectile : public Sprite2D
{
protected:
	GLfloat m_speed;
	GLint	m_damage;
	std::shared_ptr<Enemy> m_target;
public:
	Projectile();
	Projectile(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat speed, GLint damage);
	~Projectile();
	
	void Seek(std::shared_ptr<Enemy> target);
	void Update(GLfloat deltaTime) override;
	void HitTarget(GLfloat deltaTime, GLfloat speed);
	std::shared_ptr<Sprite2D> m_sprite;
	void Reset();
	void Set2DRotation();
};

