#include "Tower.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"
#include "Sprite2D.h"
#include "GameManager/ResourceManagers.h"
#include "Enemy.h"

#include <cmath>

Tower::Tower() : Sprite2D()
{
	m_isEnable = false;
}

Tower::Tower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat range, GLfloat fireRate, GLfloat fireCount, GLint cost)
	: Sprite2D(model, shader, texture) 
{
	m_range = range;
	m_fireRate = fireRate;
	m_fireCount = fireCount;
	m_cost = cost;
	m_isShooted = false;
	m_nearestEnemy = nullptr;
}

Tower::~Tower() 
{

}

void Tower::Update(GLfloat deltaTime, std::list<std::shared_ptr<Enemy>> listEnemy, std::list < std::shared_ptr<Arrow>>& listArrow)
{	
	UpdateTarget(listEnemy);
	if (m_target == nullptr)	return;
	if (m_target->m_currentHealth <= 0)
	{
		m_target = nullptr;
		return;
	}
	else
		if(m_fireCount <= 0){
			listArrow.push_back(ShootArrow());
			m_fireCount = 1.f / m_fireRate;
		}
	m_fireCount -= deltaTime;
	m_isShooted = false;
}

void Tower::UpdateTarget(std::list<std::shared_ptr<Enemy>> listEnemies)
{
	GLfloat shortestDistance = std::numeric_limits<float>::infinity();

	for (auto& enemy : listEnemies)
	{
		Vector2 deltaMove = Get2DPosition() - enemy->Get2DPosition();
		float distanceToEnemy = sqrt((deltaMove.x * deltaMove.x) + (deltaMove.y * deltaMove.y));
		if (distanceToEnemy < shortestDistance)
		{
			shortestDistance = distanceToEnemy;
			m_nearestEnemy = enemy;
		}
	}
	// Lock on to the nearest enemy
	if (m_nearestEnemy != nullptr && shortestDistance <= m_range)
	{
		m_target = m_nearestEnemy;
	}
	// Stop tracking if the enemy is out of range
	if (shortestDistance > m_range)
	{
		m_target = nullptr;
	}
}

std::shared_ptr<Arrow> Tower::ShootArrow() 
{
	std::shared_ptr<Arrow> arrow = ArrowPooling::GetInstance()->GetFromPool();
	if (arrow != nullptr)
	{
		arrow->SetPosition(m_position);
		arrow->Seek(m_target);
	}
	ResourceManagers::GetInstance()->PlaySound("rock.wav");
	return arrow;
}

void Tower::Reset() 
{
	this->DisableObject();
	Set2DPosition(0, 0);
}
