#pragma once
#include "SpriteAnimation.h"
#include "Sprite2D.h"
#include "GamePool/PoolableObject.h"

class Sprite2D;
class Enemy : public SpriteAnimation, public Poolable
{
private:
	GLint	m_maxHealth;
	GLfloat	m_speed;
	GLint	m_targetIndex;
public:
	Enemy();
	Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint health, GLfloat speed, std::list<std::shared_ptr<Sprite2D>> targets);
	~Enemy();

	std::list<std::shared_ptr<Sprite2D>>	m_listTargets;
	std::shared_ptr<Sprite2D>	m_target;
	Vector2						m_moveDir;
	GLint						m_currentHealth;

	void	EnemyMovement(GLfloat deltatime, GLfloat speed, Vector2 moveDir);
	void	Update(GLfloat deltatime) override;
	void	SeekTarget();
	void	LockTarget();
	Vector2		Get2DPosition();
	void Reset() override;
};

