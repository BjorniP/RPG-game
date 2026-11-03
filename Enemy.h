#pragma once
#include "Entity.h"
#include"EnemySpawnerTile.h"
class Enemy :
    public Entity
{
protected:
   unsigned Exp;
   EnemySpawnerTile& enemySpawnerTile;
   sf::Clock damageTimer;
   sf::Int32 damageTimerMax;
   sf::Clock despawnTimer;
   sf::Int32 despawnTimerMax;


   virtual void initVariables()=0;
   virtual void initAnimation()=0;
public:

    Enemy(EnemySpawnerTile& enemy_spwaner_tile);
    virtual ~Enemy();

    //Accessors
   const unsigned& gainExp() const;
   EnemySpawnerTile& getEnemySpawnerTile();
   const bool getDamageTimerDone() const;
   const bool getDespawnTimerDone() const;

   //Modifier
   void resetDamageTimer();


    //Funcitons

   virtual void generateAttributes(const unsigned level);
   virtual void loseHp(const int hp);
   virtual const bool isDead() const;
   virtual const AttributeComponent* getAttributeComp() const;
   virtual void updateAnimation(const float& dt)=0;
   virtual void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
   virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL,
        const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false)=0;
};

