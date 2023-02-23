#pragma once
#include "Projectile.h"
class Arrow : public Projectile
{
public:
	Arrow(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Arrow();
};

