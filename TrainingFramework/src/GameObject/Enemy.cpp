#include "Enemy.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"

#include <math.h>

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint health, GLfloat speed, std::shared_ptr<Sprite2D> target)
	:SpriteAnimation(model, shader, texture, 12, 1, 0, 0.1f)
{
	m_health = health;
	m_speed = speed;
	m_target = target;
}

Enemy::~Enemy()
{

}

void Enemy::EnemyMovement(GLfloat deltatime, GLfloat speed, std::shared_ptr<Sprite2D> target)
{
	Vector2 tPosition = target->Get2DPosition();
	Vector2 currentFramePos = Get2DPosition();
	Vector2 moveDir = (tPosition - currentFramePos).Normalize();
	float distanceThisFrame = sqrt(pow(tPosition.x - currentFramePos.x, 2) + pow(tPosition.y - currentFramePos.y, 2));
	if (distanceThisFrame <= deltatime * speed) {
		Set2DPosition(tPosition.x, tPosition.y);
		//Then fine the next waypoint
	}
	Set2DPosition(currentFramePos.x + moveDir.x * deltatime * speed, currentFramePos.y + moveDir.y * deltatime * speed);

}

void Enemy::Update(GLfloat deltatime) 
{	
	EnemyMovement(deltatime, m_speed, m_target);
	m_currentTime += deltatime;
	if (m_currentTime >= m_frameTime)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames)
			m_currentFrame = 0;
		m_currentTime -= m_frameTime;
	}

}