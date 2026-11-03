#pragma once
#include "Weapon.h"
class RangedWeapons :
    public Weapon
{
private:

protected:

public:
    RangedWeapons(unsigned level,unsigned value, std::string texture_file);
    virtual ~RangedWeapons();

    virtual RangedWeapons* clone() = 0;
    virtual void generate(const unsigned levelMax, const unsigned levelMin);
    virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

