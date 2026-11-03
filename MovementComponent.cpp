#include "stdafx.h"
#include "MovementComponent.h"

//Cons/Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite,float maxVelocity,float acceleration,float deceleration)
	:sprite(sprite),maxVelocity(maxVelocity),acceleration(acceleration),deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{
	//std::cout << "MovementComponent.cpp\n";
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

//Accessors
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;

	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;

	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;

	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;

	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;

	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	}
	return false;
}

void MovementComponent::stopVelocity()
{
	/*Resets the velocity*/
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	/*Resets the velocity*/
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	/*Resets the velocity*/
	this->velocity.y = 0.f;
}

//Public functions
void MovementComponent::move(const float dir_x, const float dir_y,const float& dt)
{
	//Accelaration
	this->velocity.x += this->acceleration * dir_x * dt;
    this->velocity.y += this->acceleration * dir_y * dt;


}

void MovementComponent::update(const float& dt)
{
	/*Decelerates the sprite and controls the max velocity*/
	//Sprite moves depending in the velocity
	//Checking directions
	if (this->velocity.x > 0.f)//check for right(positive x)
	{
		//Check for max velocity in the right
		if (this->velocity.x > this->maxVelocity)
		{
			this->velocity.x = this->maxVelocity;
		}

		//Deceleration
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	else if (this->velocity.x < 0.f)//check for left(negative x)
	{
		//Check for max velocity in the left 
		if (this->velocity.x < -this->maxVelocity)
		{
			this->velocity.x = -this->maxVelocity;
		}

		//Deceleration
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	if (this->velocity.y > 0.f)//check for down(positive y)
	{
		//Check for max velocity in the right
		if (this->velocity.y > this->maxVelocity)
		{
			this->velocity.y = this->maxVelocity;
		}

		//Deceleration
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	else if (this->velocity.y < 0.f)//check for up(negative y)
	{
		//Check for max velocity in the left 
		if (this->velocity.y < -this->maxVelocity)
		{
			this->velocity.y = -this->maxVelocity;
		}

		//Deceleration
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
		{
			this->velocity.y = 0.f;
		}
	}

	this->sprite.move(this->velocity * dt);//uses velocity
}
