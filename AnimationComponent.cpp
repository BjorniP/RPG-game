 #include "stdafx.h"
#include "AnimationComponent.h"

//Cons/Destructors
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite),TextureSheet(texture_sheet),lastAnimation(NULL),priorityAnimation(NULL)
{

}
//bcg
AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

const bool AnimationComponent::isSet(const std::string key)
{
	if (this->lastAnimation != NULL)
	{
		return true;
	}
	return false;
}

const bool AnimationComponent::isChanged(const std::string key)
{
	if (this->priorityAnimation == NULL)
	{
		return true;
	}
	return false;
}

//Public functions
void AnimationComponent::addAnimations(const std::string key, float animation_timer,
	int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height)
{
	this->animations[key] = new Animation(
		this->sprite, this->TextureSheet, animation_timer,
		start_frame_x, start_frame_y, frame_x, frame_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	if (this->priorityAnimation)//Check if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])//Check if is the same as the current animation played
		{//if it is,animation plays as a regular one
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			if (this->animations[key]->play(dt))//when the play finishes remove the priority 
			{
				this->priorityAnimation = NULL;
			}

		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt);
	}
	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max
, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			if (this->animations[key]->play(dt, abs((modifier / modifier_max))))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt, abs((modifier / modifier_max)));
	}
	return this->animations[key]->isDone();
}
