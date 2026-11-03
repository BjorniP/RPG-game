#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->weapon = new Sword(1, 1, 4, 50, 20, "C:\\VSmain\\repos\\Project2\\Resources\\Player\\sword.png");
	this->weapon->generate(3, 1);
	this->damageTimermax = 500.f;
}

void Player::initComponents()
{

}

void Player::initAnimation()
{
	this->animationComponent->addAnimations("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimations("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimations("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimations("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimations("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimations("ATTACK", 6.f, 12, 1, 15, 1, 64, 64);
}

void Player::initInventory()
{
	this->inventory = new Inventory(100);
}

//Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();


	this->createSkillComponent();
	//std::cout << this->skillComponent->getSkill("endurance") << "\n";

	this->createHitboxComponent(this->sprite, 16.f, 26.f, 32.f, 38.f);
	this->createMovementComponent(140.f, 1400.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->setPosition(x, y);

	this->initAnimation();
	this->initInventory();
}

Player::~Player()
{
	delete this->weapon;
	delete this->inventory;
}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

Weapon* Player::getWeapon() const
{
	return this->weapon;
}

const std::string Player::toStringCharacterTab() const
{
	std::stringstream ss;
	const AttributeComponent* ac = this->attributeComponent;
	const Weapon* w = this->weapon;
	ss << "Level: " << ac->level << "\n"
		<< "Health: " << ac->hp << "\n"
		<< "Health Max" << ac->hpMax << "\n"
		<< "Experience: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext << "\n"
		<< "Weapon Level: " << w->getLevel() << "\n"
		<< "Weapon Type: " << w->getType() << "\n"
		<< "Weapon Value: " << w->getValue() << "\n"
		<< "Weapon Range: " << w->getRange() << "\n"
		<< "Weapon Damage Min: " << w->getDamageMin() + this->attributeComponent->damageMin << " Dmg without weapon (" << this->attributeComponent->damageMin << ")" << "\n"
		<< "Weapon Damage Max: " << w->getDamageMax() + this->attributeComponent->damageMax << " Dmg without weapon (" << this->attributeComponent->damageMax << ")" << "\n"
		<< "Vitality: " << ac->vitality << "\n"
		<< "Strength: " << ac->strength << "\n"
		<< "Agility: " << ac->agility << "\n"
		<< "Dexterity: " << ac->dexterity << "\n"
		<< "Intelligence: " << ac->intelligence << "\n"
		<< "Attribute Points: " << ac->attributePoints << "\n";

	return ss.str();
}

const bool& Player::getInitAttack() const
{
	return this->initAttack;
}

const bool Player::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimermax)
	{
		this->damageTimer.restart();
		return true;
	}
	return false;
}

const unsigned Player::getDamage() const
{
	return rand() % ((this->attributeComponent->damageMax + this->weapon->getDamageMax())
		- (this->attributeComponent->damageMin + this->weapon->getDamageMin()) + 1)
		+ (this->attributeComponent->damageMin + this->weapon->getDamageMin());
}

void Player::setInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}

void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Player::loseExp(const int exp)
{
	this->attributeComponent->loseExp(exp);
}

void Player::gainExp(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

//Functions

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		
	}
	else
	{
		if (this->movementComponent->getState(IDLE))
			this->animationComponent->play("IDLE", dt);

		else if (this->movementComponent->getState(MOVING_LEFT))
		{
			this->animationComponent->play
			(
				"WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity()
			);
		}
		else if (this->movementComponent->getState(MOVING_RIGHT))
		{
			this->animationComponent->play
			(
				"WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity()
			);
		}
		else if (this->movementComponent->getState(MOVING_UP))
		{
			this->animationComponent->play
			(
				"WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity()
			);
		}
		else if (this->movementComponent->getState(MOVING_DOWN))
		{
			this->animationComponent->play
			(
				"WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity()
			);
		}
	}
	
}

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->attributeComponent->gainExp(20);
	std::cout << this->attributeComponent->debugPrint();*/
     
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
	this->attributeComponent->update();

	this->weapon->update(mouse_pos_view, sf::Vector2f(this->getSpriteCenter().x, this->getSpriteCenter().y + 5.f));

}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", light_position);
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("light", light_position);
		this->weapon->render(target, shader);
	}
	else
	{
		target.draw(this->sprite);
		this->weapon->render(target);
	}
	
	if (show_hitbox)
	{
		hitboxComponent->render(target);
	}
}
