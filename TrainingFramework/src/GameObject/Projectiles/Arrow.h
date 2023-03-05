#pragma once
#include "Projectile.h"
#include "GameManager/ResourceManagers.h"
class Arrow : public Projectile
{
public:
	Arrow(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture) : Projectile(model, shader, texture, 10.0f, 20){};
	~Arrow() {};
};

