#include "Projectile.h"
#include "Enemy.h"
#include "GamePool/ArrowPooling.h"

Projectile::Projectile() : Sprite2D()
{
	m_isEnable = false;
}

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
	if (IsEnable()) HitTarget(deltaTime, m_speed);
	else 
	{
		ArrowPooling::GetInstance()->ReturnToPool(std::static_pointer_cast<Arrow>(shared_from_this()));
		return;
	}
}

void Projectile::HitTarget(GLfloat deltaTime, GLfloat speed) 
{
	if (m_target == nullptr) return;
	Vector2 tPosition = m_target->Get2DPosition();
	Vector2 currentFramePos = this->Get2DPosition();
	Vector2 deltaMove_Alter = tPosition - currentFramePos;
	Vector2 deltaMove2 = deltaMove_Alter;
	Vector2 deltaMove = deltaMove_Alter.Normalize() * deltaTime * speed;
	if (deltaMove2.x * deltaMove2.x <= deltaMove.x * deltaMove.x || deltaMove2.y * deltaMove2.y <= deltaMove.y * deltaMove.y) //reached the target
	{
		Set2DPosition(tPosition.x, tPosition.y);
		m_target->m_currentHealth -= m_damage;
		Reset();
		return;
	}
	currentFramePos += deltaMove_Alter * deltaTime * speed;
	//Update the position of the sprite
	Set2DPosition(currentFramePos.x, currentFramePos.y);
}

void Projectile::Reset() 
{
	this->DisableObject();
	this->Set2DPosition(0, 0);
}