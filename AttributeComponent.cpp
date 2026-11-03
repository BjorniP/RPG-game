#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = (40 * pow(this->level, 3) - 140 * pow(this->level, 2) + (UINT64)300 * this->level) / 3;
	this->attributePoints = 2;

	this->MaximumSkill = 10;
	this->vitality = 1;
	this->strength = 1;
	this->agility = 1;
	this->dexterity = 1;
	this->intelligence = 1;
	this->updatelevelUp(); 
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
	
}


//Functions

const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
}

const bool AttributeComponent::VitalityMax()
{
	if (this->vitality >= this->MaximumSkill)
	{
		return true;
	}
	return false;
}

const bool AttributeComponent::AgilityMax()
{
	if (this->agility >= this->MaximumSkill)
	{
		return true;
	}
	return false;
}

const bool AttributeComponent::IntelligenceMax()
{
	if (this->intelligence >= this->MaximumSkill)
	{
		return true;
	}
	return false;
}

const bool AttributeComponent::DexterityMax()
{
	if (this->dexterity >= this->MaximumSkill)
	{
		return true;
	}
	return false;
}

const bool AttributeComponent::StrengthMax()
{
	if (this->strength >= this->MaximumSkill)
	{
		return true;
	}
	return false;
}

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;
	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp Next: " << this->expNext << "\n"
		<< "Attp: " << this->attributePoints << "\n";
	return ss.str();
}

void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax = this->vitality * 5 + this->agility * 2 + this->strength * 3 + this->intelligence * 2 + this->dexterity;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	/*this->defence = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->accuracy = this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
	this->luck = this->intelligence * 2 + this->intelligence / 5;*/
	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::loseExp(const int exp)
{
	this->exp -= exp;
	if (this->exp < 0)
	{
		this->exp = 0;
	}

}


void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;

	this->updatelevelUp();
}

void AttributeComponent::removeAttributePoints()
{
	this->attributePoints--;
}

void AttributeComponent::updatelevelUp()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		this->hp = this->hpMax;
		this->exp -= this->expNext;
		this->expNext = (40 * pow(this->level, 3) - 140 * pow(this->level, 2) + (UINT64)300 * this->level) / 3;
		//this->expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;

		//calculating attribute points
		if (this->intelligence == this->MaximumSkill && this->agility == this->MaximumSkill
			&& this->strength == this->MaximumSkill && this->dexterity == this->MaximumSkill
			&& this->vitality == this->MaximumSkill)
		{
			this->attributePoints = 0;
		}
		else
		{
			int addPoints = (pow(this->level, 2) - (this->level * 2));
			if (addPoints <= 0)
			{
				addPoints = 1;
			}
			this->attributePoints += addPoints;
		}
		this->updateStats(true);
	}
}

void AttributeComponent::update()
{
	this->updatelevelUp();
}
