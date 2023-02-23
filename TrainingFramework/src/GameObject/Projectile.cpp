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
	Vector2 tPosition = m_target->Get2DPosition();
	Vector2 currentFramePos = this->Get2DPosition();
	Vector2 deltaMove2 = tPosition - currentFramePos;
	Vector2 deltaMove = deltaMove2.Normalize() * deltaTime * speed;
	if (deltaMove2.x * deltaMove2.x <= deltaMove.x * deltaMove.x || deltaMove2.y * deltaMove2.y <= deltaMove.y * deltaMove.y) //reached the target
	{
		Set2DPosition(tPosition.x, tPosition.y);
		return;
	}
	currentFramePos += deltaMove2.Normalize() * deltaTime * speed;
	//Update the position of the sprite
	Set2DPosition(currentFramePos.x, currentFramePos.y);
}