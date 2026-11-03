#include "stdafx.h"
#include "RegularTile.h"

RegularTile::RegularTile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& tileTexture, const sf::IntRect& texture_rect,
	bool collision) 
	:Tile(type, grid_x,grid_y,gridSizeF,tileTexture,texture_rect,collision)
{
	
}

RegularTile::~RegularTile()
{
}

const std::string RegularTile::getAsString() const
{
	std::stringstream ss;
	ss << this->type << " " << shape.getTextureRect().left << " " << shape.getTextureRect().top <<
		" " << this->collision;
	return ss.str();
}
const bool RegularTile::removeCollision()
{
	if (this->collision == false)
	{
		return false;
	}
	else
	{
		this->collision = false;
		return true;
	}
}

void RegularTile::update()
{
}

void RegularTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", player_position);
		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
