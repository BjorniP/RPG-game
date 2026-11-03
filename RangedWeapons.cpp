#include "stdafx.h"
#include "RangedWeapons.h"

RangedWeapons::RangedWeapons(unsigned level, unsigned value, std::string texture_file)
	:Weapon(level,value,texture_file)
{
	this->type = ItemTypes::IT_RANGEDWEAPON;
}

RangedWeapons::~RangedWeapons() 
{

}

void RangedWeapons::generate(const unsigned levelMax, const unsigned levelMin)
{

}
