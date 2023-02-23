#include "Projectile.h"
#include "Enemy.h"


Projectile::Projectile(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat speed, GLint damage)
	: Sprite2D(model, shader, texture)
{
	m_speed = speed;
	m_damage = damage;
}

Projectile::~Projectile() 
{

}

void Projectile::Seek(std::shared_ptr<Enemy> target)
{
	m_target = target;
}

void Projectile::Update(GLfloat deltaTime) 
{
	HitTarget(deltaTime, m_speed);
}

void Projectile::HitTarget(GLfloat deltaTime, GLfloat speed) 
{
	if (m_target = nullptr) return;
	Vector2 moveDir = m_target->Get2DPosition() - Get2DPosition();
	Vector2 currentFramePos = Get2DPosition();
	float distanceThisFrame = sqrt(moveDir.x * moveDir.x + moveDir.y * moveDir.y);
	if (distanceThisFrame <= deltaTime * speed) 
	{
		//HitTarget();
		return;
	}
	currentFramePos += moveDir.Normalize() * deltaTime * speed;
}