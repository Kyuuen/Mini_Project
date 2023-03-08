#include "Enemy.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"
#include "GameManager/ResourceManagers.h"
#include "GamePool/EnemyPooling.h"

#include <math.h>

Enemy::Enemy() : SpriteAnimation()
{	
	m_isEnable = false;
	m_maxHealth = 10;
	m_currentHealth = m_maxHealth;
	m_speed = 200;
	m_targetIndex = 0;
	Set2DPosition(50, 900);
	SetSize(70, 70);
}
Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint maxHealth, GLfloat speed, std::list<std::shared_ptr<Sprite2D>> targets)
	:SpriteAnimation(model, shader, texture, 18, 1, 0, 0.1f)
{
	m_maxHealth = maxHealth;
	m_currentHealth = m_maxHealth;
	m_speed = speed;
	m_listTargets = targets;
	m_targetIndex = 0;
}

Enemy::~Enemy()
{

}

void Enemy::LockTarget() 
{	
	if (m_targetIndex >= m_listTargets.size()) {
		GameMaster::GetInstance()->EnemyBreakThrough();
		Reset();
		return;
	}
	std::list<std::shared_ptr<Sprite2D>>::iterator it = std::begin(m_listTargets);
	std::advance(it, m_targetIndex);	//move the pointer to the target's index
	m_target = *it;

	SeekTarget();
	m_targetIndex++;
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
	Vector2 deltaMove = moveDir.Normalize() * deltatime * speed;
	Vector2 tPosition = m_target->Get2DPosition();
	Vector2 currentFramePos = Get2DPosition();
	Vector2 deltaMove2 = tPosition - currentFramePos;
	if (deltaMove2.x * deltaMove2.x <= deltaMove.x* deltaMove.x || deltaMove2.y * deltaMove2.y <= deltaMove.y * deltaMove.y) //reached the target
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
	if (!IsAlive()) this->DisableObject();
	if (IsEnable()) {
		EnemyMovement(deltatime, m_speed, m_moveDir);
		m_currentTime += deltatime;
		if (m_currentTime >= m_frameTime)
		{
			m_currentFrame++;
			if (m_currentFrame >= m_numFrames)
				m_currentFrame = 0;
			m_currentTime -= m_frameTime;
		}
	}else EnemyPooling::GetInstance()->ReturnToPool(std::static_pointer_cast<Enemy>(shared_from_this()));
}

void Enemy::Reset() 
{
	this->DisableObject();
	Set2DPosition(0, 0);
}

void Enemy::GetListTarget(std::list<std::shared_ptr<Sprite2D>> targets)
{
	m_listTargets = targets;
}

bool Enemy::IsAlive() 
{
	if (m_currentHealth <= 0) return false;
}
