#pragma once
#include "SpriteAnimation.h"
#include "Sprite2D.h"
class Enemy : public SpriteAnimation
{
private:
	GLint	m_health;
	GLfloat	m_speed;
public:
	Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint health, GLfloat speed, std::shared_ptr<Sprite2D> target);
	~Enemy();

	std::shared_ptr<Sprite2D>	m_target;
	Vector2		m_moveDir;

	void	EnemyMovement(GLfloat deltatime, GLfloat speed, std::shared_ptr<Sprite2D> target);
	void	Update(GLfloat deltatime) override;
};

