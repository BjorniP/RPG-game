#pragma once
//all directories are included in all other classes
#include"HitboxComponent.h"
#include"MovementComponent.h"
#include"AnimationComponent.h"
#include"AttributeComponent.h"
#include"SkillComponent.h"
class Entity
{
private:
	void initVariables();
protected:
	//Variables for the character
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;
     
public:
	//Cons/Destructors
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float decelartion);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);
	void createSkillComponent();
	void createAIComponent();
	
	//Public functions
	//Accessors
	virtual MovementComponent* getMovementComponent();
	virtual AnimationComponent* getAnimationComponent();
	virtual AttributeComponent* getAttributeComponent();
	virtual SkillComponent* getSkillComponent();

	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f& getSpritePosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2f getSpriteCenter() const;
	virtual const sf::Vector2i getGridPosition(const int gridsizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	virtual const float getDistance(const Entity& entity) const;
	virtual const float getSpriteDistance(const Entity& entity) const;
	//Modifiers
	virtual void setPosition(const float x, const float y);
	//Functions
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view,const sf::View& view) = 0;
	virtual void render(sf::RenderTarget& target,sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox) = 0;
};

