#include "Tower.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"
#include "Sprite2D.h"
#include "GameManager/ResourceManagers.h"

#include <cmath>

Tower::Tower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat range, GLfloat fireRate, GLfloat fireCount, GLint cost)
	: Sprite2D(model, shader, texture) 
{
	m_range = range;
	m_fireRate = fireRate;
	m_fireCount = fireCount;
	m_cost = cost;
}

Tower::~Tower() 
{

}

void Tower::Update(GLfloat deltaTime) 
{	
	UpdateTarget(m_listEnemies);
	if (m_target = nullptr)	return;
	/*if (m_target->GetCurrentHealth() <= 0)
	{
		m_target = nullptr;
		return;
	}*/
	else
		if(m_fireCount <= 0){
			//Shoot();
			m_fireCount = 1.f / m_fireRate;
		}
	m_fireCount -= deltaTime;
}

void Tower::UpdateTarget(std::list<std::shared_ptr<Enemy>> listEnemies)
{
	GLfloat shortestDistance = std::numeric_limits<float>::infinity();
	std::shared_ptr<Enemy>	nearestEnemy = nullptr;
	for (auto& enemy : listEnemies)
	{
		float distanceToEnemy = std::sqrt(std::pow(m_position.x - enemy->Get2DPosition().x, 2) +
			std::pow(m_position.y - enemy->Get2DPosition().y, 2));
		if (distanceToEnemy < shortestDistance)
		{
			shortestDistance = distanceToEnemy;
			nearestEnemy = enemy;
		}
	}
	// Lock on to the nearest enemy
	if (nearestEnemy != nullptr && shortestDistance <= m_range)
	{
		m_target = nearestEnemy;
	}
	// Stop tracking if the enemy is out of range
	if (shortestDistance > m_range)
	{
		m_target = nullptr;
	}
}

void Tower::Shoot(std::shared_ptr<Sprite2D> bullet) 
{	
	m_bullet = bullet;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("arrow.tga");
	m_bullet = std::make_shared<Sprite2D>(model, shader, texture);

	m_bullet->Set2DPosition(400, 500);
	m_bullet->SetSize(60, 80);
}
