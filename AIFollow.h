#pragma once
#include "AIOption.h"
class AIFollow :
    public AIOption
{
public:
    AIFollow(Entity& self, Entity& entity);
    virtual ~AIFollow();

    void update(const float& dt);
};

