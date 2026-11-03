#include "stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& tileTexture, const sf::IntRect& texture_rect,
	int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)
	:Tile(TileTypes::ENEMYSPAWNER,grid_x, grid_y, gridSizeF, tileTexture, texture_rect,false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->firstSpawn = true;
}

EnemySpawnerTile::~EnemySpawnerTile()
{
}

const std::string EnemySpawnerTile::getAsString() const
{
	std::stringstream ss;
	ss << this->type << " " << shape.getTextureRect().left << " " << shape.getTextureRect().top <<" "<< this->enemyType << " "
		<< this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;
	return ss.str();
}


const int& EnemySpawnerTile::getEnemyCounter() const
{
	return this->enemyCounter;
}

const int& EnemySpawnerTile::getEnemyAmount() const
{
	return this->enemyAmount;
}

const bool EnemySpawnerTile::getSpawnTimer()
{
	if (this->enemySpawnTimer.getElapsedTime().asSeconds() >= this->enemyTimeToSpawn || this->firstSpawn)
	{
		this->enemySpawnTimer.restart();
		this->firstSpawn = false;
		return true;
	}
	   return false;
}


void EnemySpawnerTile::increaseEnemyCounter()
{
	if (this->enemyCounter < this->enemyAmount)
		++this->enemyCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter()
{
	if (this->enemyCounter > 0)
		--this->enemyCounter;
}

const bool EnemySpawnerTile::removeCollision()
{
	if (this->collision = false)
	{
		return false;
	}
	else
	{
		this->collision = false;
		return true;
	}
}
void EnemySpawnerTile::update()
{
	
}

void EnemySpawnerTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
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



