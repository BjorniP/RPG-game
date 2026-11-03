#include "stdafx.h"
#include "AIComponent.h"

AIComponent::AIComponent(Entity& self, Entity& entity)
	:entity(entity),self(self)
{
}

AIComponent::~AIComponent()
{
}

void AIComponent::update(const float& dt)
{
}
