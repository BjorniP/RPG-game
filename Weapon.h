#pragma once
#include "Item.h"
class Weapon :
    public Item
{
private:
	void initVariables();
protected:
	unsigned range;
	unsigned damageMin;
	unsigned damageMax;
	sf::Sprite weapon_sprite;
	sf::Texture weapon_texture;

	sf::Clock attackTimer;
	sf::Int32 attackTimerMax;
public:
	Weapon(unsigned level, unsigned value,std::string texture_file);
	Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range,unsigned value,std::string texture_file);
	virtual ~Weapon();

	const unsigned& getRange() const;
	const unsigned& getDamageMin() const;
	const unsigned& getDamageMax() const;
	const unsigned getDamage() const;
	const bool getAttackTimer();

	//const sf::Vector2i& getPosition(const int gridSizeI) const;

	virtual Item* clone() = 0;
	virtual void generate(const unsigned levelMax, const unsigned levelMin) = 0;
	virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

