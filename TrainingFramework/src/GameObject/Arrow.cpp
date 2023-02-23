#include "Arrow.h"
#include "Projectile.h"

Arrow::Arrow(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Projectile(model, shader, texture, 10, 10) 
{
}

Arrow::~Arrow(){}