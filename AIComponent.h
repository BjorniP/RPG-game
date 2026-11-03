#pragma once
#include"Entity.h"
#include"AIFollow.h"
class AIComponent
{
private:
	Entity& self;
	Entity& entity;
public:
	AIComponent(Entity& self, Entity& entity);
	virtual ~AIComponent();

	void update(const float& dt);
};

