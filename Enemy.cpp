#include "stdafx.h"
#include "Enemy.h"


void Enemy::initVariables()
{
	this->Exp = 10;
	this->damageTimerMax = 1000;
	this->despawnTimerMax = 1000;
}

void Enemy::initAnimation()
{
}

//Constructor/Destructor
Enemy::Enemy(EnemySpawnerTile& enemy_spwaner_tile)
	:enemySpawnerTile(enemy_spwaner_tile)
{
	this->initVariables();
	this->initAnimation();
}

Enemy::~Enemy()
{
}

const unsigned& Enemy::gainExp() const
{
	return this->Exp;
}

EnemySpawnerTile& Enemy::getEnemySpawnerTile()
{
	return this->enemySpawnerTile;
}

const bool Enemy::getDamageTimerDone() const
{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const bool Enemy::getDespawnTimerDone() const
{
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

void Enemy::resetDamageTimer()
{
	this->damageTimer.restart();
}

void Enemy::generateAttributes(const unsigned level)
{
	this->Exp = level * 5 + (rand() % 5 + 1);
}

void Enemy::loseHp(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}

const AttributeComponent* Enemy::getAttributeComp() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent;
	}
	else
	{
		std::cout << "COULDNT INITIALIZE ATTRIBUTE COMPONENT" << "\n";
		return nullptr;
	}
}

void Enemy::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	if (vectorDistance(this->getPosition(),view.getCenter()) < 1500.f)
	{
		this->despawnTimer.restart();
	}
}



const bool Enemy::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}
	return false;
}