#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	this->range = 50;
	this->damageMin = 1;
	this->damageMax = 2;
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}

Weapon::Weapon(unsigned level, unsigned value, std::string texture_file)
	:Item(level,value)
{
	this->initVariables();
	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "COULDNT LOAD THE FILE::Weapon texture_file";
	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file)
	:Item(level,value)
{
	this->initVariables();
	this->damageMin = damageMin;
	this->damageMax = damageMax;
	this->range= range;
	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "COULDNT LOAD THE FILE::Weapon texture_file";
	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::~Weapon()
{
}

const unsigned& Weapon::getRange() const
{
	return this->range;
}

const unsigned& Weapon::getDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapon::getDamageMax() const
{
	return this->damageMax;
}

const unsigned Weapon::getDamage() const
{
	return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
}

const bool Weapon::getAttackTimer()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}
	return false;
}
//const sf::Vector2i& Weapon::getPosition(const int gridSizeI) const
//{
//	int x = static_cast<int>(this->weapon_sprite.getPosition().x) /gridSizeI;
//	int y = static_cast<int>(this->weapon_sprite.getPosition().y)/ gridSizeI;
//	sf::Vector2i Position(x, y);
//	return Position;
//}
