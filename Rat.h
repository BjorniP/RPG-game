#pragma once
#include "Enemy.h"
#include"AIFollow.h"
class Rat :
    public Enemy
{
private:
    void initVariables();
    void initAnimation();
    void initAI();
    void initGUI();

    sf::RectangleShape hpBar;

    AIFollow* follow;

public:
    Rat(float x, float y, sf::Texture& texture_sheet,EnemySpawnerTile& enemy_spwaner_tile, Entity& player);
    virtual ~Rat();

   
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL,
        const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

