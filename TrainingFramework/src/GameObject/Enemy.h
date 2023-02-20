#pragma once
#include "SpriteAnimation.h"
#include "Sprite2D.h"

class Sprite2D;
class Enemy : public SpriteAnimation
{
private:
	GLint	m_health;
	GLfloat	m_speed;
	
public:
	Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint health, GLfloat speed, std::list<std::shared_ptr<Sprite2D>> targets);
	~Enemy();

	std::list<std::shared_ptr<Sprite2D>>	m_listTargets;
	std::shared_ptr<Sprite2D>	m_target;
	Vector2						m_moveDir;


	void	EnemyMovement(GLfloat deltatime, GLfloat speed, Vector2 moveDir);
	void	Update(GLfloat deltatime) override;
	void	SeekTarget();
	void	LockTarget();
};

