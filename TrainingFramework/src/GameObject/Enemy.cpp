#include "Enemy.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"

#include <math.h>

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint maxHealth, GLfloat speed, std::list<std::shared_ptr<Sprite2D>> targets)
	:SpriteAnimation(model, shader, texture, 12, 1, 0, 0.1f)
{
	m_maxHealth = maxHealth;
	m_currentHealth = maxHealth;
	m_speed = speed;
	m_listTargets = targets;
}

Enemy::~Enemy()
{

}

void Enemy::LockTarget() 
{	
	static GLint waypointIndex = 0;
	if (waypointIndex >= m_listTargets.size() - 1) {
		//Endpath();
		return;
	}
	std::list<std::shared_ptr<Sprite2D>>::iterator it = std::begin(m_listTargets);
	std::advance(it, waypointIndex);	//move the pointer to the target's index
	m_target = *it;

	SeekTarget();
	waypointIndex++;
}

void Enemy::SeekTarget()
{	
	if (m_target == nullptr) {
		return;
	}
	m_moveDir.x = m_target->Get2DPosition().x - Get2DPosition().x;
	m_moveDir.y = m_target->Get2DPosition().y - Get2DPosition().y;
}

void Enemy::EnemyMovement(GLfloat deltatime, GLfloat speed, Vector2 moveDir)
{
	Vector2 tPosition = m_target->Get2DPosition();
	Vector2 currentFramePos = this->Get2DPosition();
	float distanceThisFrame = sqrt(pow(tPosition.x - currentFramePos.x, 2) + pow(tPosition.y - currentFramePos.y, 2));
	if (distanceThisFrame <= 10.f) //reached the target
	{
		Set2DPosition(tPosition.x, tPosition.y);
		LockTarget();	//Find new target
		return;
	}
	currentFramePos += moveDir.Normalize() * deltatime * speed;
	//Update the position of the sprite
	Set2DPosition(currentFramePos.x, currentFramePos.y);
}

Vector2 Enemy::Get2DPosition()
{
	Vector2 pos;
	pos.x = m_position.x;
	pos.y = m_position.y;
	return pos;
}

void Enemy::Update(GLfloat deltatime) 
{	
	EnemyMovement(deltatime, m_speed, m_moveDir);
	m_currentTime += deltatime;
	if (m_currentTime >= m_frameTime)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames)
			m_currentFrame = 0;
		m_currentTime -= m_frameTime;
	}
}

GLint Enemy::GetCurrentHealth() 
{
	return m_currentHealth;
}