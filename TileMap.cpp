 #include"stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	if (!this->map.empty())
	{
		for (int x = 0; x < this->map.size(); x++)//per kolonat qe jane ne boshtin e x// kemi 5000 kolona secila me nje vector tjeter
		{
			for (int y = 0; y < this->map[x].size(); y++)//secila prej kolonave ka 5000 rreshta bosh qe eshte y
			{
				for (int z = 0; z < this->map[x][y].size(); z++)//secila prej ketyre rreshtave ka 5 shtresa// sa shtresa vendosim ne vectorin [x,y] e vendosim ne
					//psh nga pese plotesojme me te dhena 3 shtresat e para dhe 2 te fundit i lem bosh;te nje vector qe ka nje shtrese me shume ka te dhenat e para por dhe nje informacion shtese
					//psh shtresa 1 ka nje siperfaqe me bar e dyta animacion te nje lugine e 3 nje peme; e4 mund te kete me shume peme dmth pyll etc
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = NULL;
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}
	
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->TextureFile = texture_file;
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector < std::vector < std::vector<Tile* > > >());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)//per kolonat qe jane ne boshtin e x// kemi 5000 kolona secila me nje vector tjeter
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)//secila prej kolonave ka 5000 rreshta bosh qe eshte y
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector < std::vector<Tile* > >());
			for (int z = 0; z < this->layers; z++)//secila prej ketyre rreshtave ka 5 shtresa// sa shtresa vendosim ne vectorin [x,y] e vendosim ne
				//psh nga pese plotesojme me te dhena 3 shtresat e para dhe 2 te fundit i lem bosh;te nje vector qe ka nje shtrese me shume ka te dhenat e para por dhe nje informacion shtese
				//psh shtresa 1 ka nje siperfaqe me bar e dyta animacion te nje lugine e 3 nje peme; e4 mund te kete me shume peme dmth pyll etc
			{
				this->map[x][y].resize(this->layers, std::vector<Tile* >());
			}
		}
    }

	if (!this->tileTextureSheet.loadFromFile(texture_file))
		std::cout << "FAILED::TILEMAP::COULDNT LOAD FROM FILE::FILENAME::" << texture_file << "\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(100, 0, 0, 50));
	//this->collisionBox.setOutlineThickness(1.f);
	//this->collisionBox.setOutlineColor(sf::Color::Red);
}

TileMap::TileMap(const std::string file_name)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(file_name);
	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(100, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}

//Accessories
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileTextureSheet;
}

const int TileMap::getTileLayers(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < this->map.size())
	{
		if (y >= 0 && y < this->map[x].size())
		{
			if (layer >= 0 && layer < this->map[x][y].size())
			{
				return static_cast<int>(this->map[x][y][layer].size());
			}
		}
	}
	return -1;
}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers
		)
	{
		return this->map[x][y][z].empty();
	}
	throw("ERROR::TILEMAP::TRYING TO ACCESS TILE OUTSIDE OF BOUNDS");
}

const bool TileMap::checkType(const int x, const int y, const int z, const int type) const
{
	return this->map[x][y][this->layer].back()->getType() == type;
}

//Functions
void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the entire tile-map in txt file
	    * Format:
		* Basic:
		* Size x y
		* gridSize
		* layers
		* texture_file

		All tiles:
		Grid pos. x y , TextureRect x y
	*/
	std::ofstream out_file;

	out_file.open(file_name);
	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->TextureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)	
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " << this->map[x][y][z][k]->getAsString() << " ";
						}
					}	
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULDNT SAVE TO FILE::FILENAME::" << file_name << "\n";
	}

	out_file.close();

}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);
	if (in_file.is_open())
	{
		//Basics
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
		this->layers = layers;
		this->TextureFile = texture_file;
		

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector < std::vector < std::vector<Tile* > > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)//per kolonat qe jane ne boshtin e x// kemi 5000 kolona secila me nje vector tjeter
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)//secila prej kolonave ka 5000 rreshta bosh qe eshte y
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector < std::vector<Tile* > >());
				for (int z = 0; z < this->layers; z++)//secila prej ketyre rreshtave ka 5 shtresa// sa shtresa vendosim ne vectorin [x,y] e vendosim ne
					//psh nga pese plotesojme me te dhena 3 shtresat e para dhe 2 te fundit i lem bosh;te nje vector qe ka nje shtrese me shume ka te dhenat e para por dhe nje informacion shtese
					//psh shtresa 1 ka nje siperfaqe me bar e dyta animacion te nje lugine e 3 nje peme; e4 mund te kete me shume peme dmth pyll etc
				{
					this->map[x][y].resize(this->layers, std::vector<Tile* >());
				}
			}
		}

		if (!this->tileTextureSheet.loadFromFile(texture_file))
			std::cout << "FAILED::TILEMAP::COULDNT LOAD FROM FILE::FILENAME::" << texture_file << "\n";

		while (in_file>> x >> y >> z >> type)
		{
			if (type == TileTypes::ENEMYSPAWNER)
			{
				int enemy_type = 0, enemy_am = 0, enemy_tts = 0, enemy_md = 0; 
				in_file >> trX >> trY >> enemy_type >> enemy_am >> enemy_tts >> enemy_md;
			
				this->map[x][y][z].push_back
				(
					new EnemySpawnerTile
					(
						x, y, this->gridSizeF, this->tileTextureSheet,
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), enemy_type, enemy_am, enemy_tts, enemy_md
					)
				);
			}
			else
			{
				in_file >>trX >> trY >> collision;
				this->map[x][y][z].push_back(
					new RegularTile
					(
						type,
						x, y, this->gridSizeF, this->tileTextureSheet,
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), collision
					)
				);
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULDNT LOAD FROM FILE::FILENAME::" << file_name << "\n";
	}

	in_file.close();
}

void TileMap::addTiles(const int x, const int y,const int z, const sf::IntRect& texture_rect,
	const bool& collision, const short& type)
{
	/* Take three indices from the mouse position in the grid and add a tile to that position,
	if the internal tilemap array allows it*/
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
			this->map[x][y][z].push_back(new RegularTile
			(type, x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, collision));	
	}

}
void TileMap::addTiles(const int x, const int y, const int z, const sf::IntRect& texture_rect,
	const int enemy_type, const int enemy_amount,const int enemy_tts,const int enemy_md)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		this->map[x][y][z].push_back(new EnemySpawnerTile
		(x, y, this->gridSizeF, this->tileTextureSheet, texture_rect,enemy_type, enemy_amount, enemy_tts, enemy_md));
	//std::cout << "DEBUG:: ADDED TILE" << "\n";
	}
	
}

const sf::Vector2i& TileMap::getMaxSizeWorldGrid() const
{
	return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeWorldF() const
{
	return this->maxSizeWorldF;
}

void TileMap::removeTiles(const int x, const int y, const int z, const int type)
{
	/* Take three indices from the mouse position in the grid and add a tile to that position,
	if the internal tilemap array allows it*/
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			if (type >= 0)
			{
				if (this->map[x][y][z].back()->getType() == type)
				{
					//Ok to remove tile
					delete this->map[x][y][z][this->map[x][y][z].size() - 1];
					this->map[x][y][z].pop_back();
					//std::cout << "DEBUG:: REMOVED TILE" << "\n";
				}
			}
			else
			{
				delete this->map[x][y][z][this->map[x][y][z].size() - 1];
				this->map[x][y][z].pop_back();
			}
			
		}
	}
}
void TileMap::removeCollision(const int x, const int y, const int z, const int type)
{
	/*std::cout << this->map[x][y][layer].back()->getCollision() << " "
		<< x << " "
		<< y << " ";*/
	if (type != this->map[x][y][z][this->map[x][y][z].size()-1]->getType())
	{
		for (int i = 0; i < this->map[x][y][z].size(); i++)
		{
			if (this->map[x][y][z][i]->removeCollision())
			{
				delete this->map[x][y][z][this->map[x][y][z].size() - 1];
				this->map[x][y][z].pop_back();
			}
		}
	}
}

void TileMap::updateWorldBoundsCollision(Entity* entity, const float& dt)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
}

void TileMap::updateTileCollision(Entity* entity, const float& dt)
{
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 5;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 7;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 5;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 7;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (this->map[x][y][this->layer][k]->getCollision() &&
					this->map[x][y][this->layer][k]->intersects(nextPositionBounds))
				{
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}
}

void TileMap::updateTiles(Entity* entity, const float& dt, EnemySystem& enemy_system)
{
	//CULLING
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 15;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 16;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 8;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 9;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				//Update the tile
				this->map[x][y][this->layer][k]->update();

				//Update the tile specifics
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER)
				{
					EnemySpawnerTile* es = dynamic_cast<EnemySpawnerTile*>(this->map[x][y][this->layer][k]);
					if (es)
					{
						if (es->getSpawnTimer() && es->getEnemyCounter() < es->getEnemyAmount())
						{
							enemy_system.createEnemy(EnemyTypes::RAT, x * this->gridSizeF, y * this->gridSizeF, *es);
						}		
					}
				}
			}
		}
	}
}
void TileMap::update(Entity* entity, const float& dt)
{
	
	
}
 
void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition,
	sf::Shader* shader, const sf::Vector2f playerPosition, const bool show_collision)
{
	this->layer = 0;

	this->fromX = gridPosition.x - 15;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = gridPosition.x + 16;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = gridPosition.y - 8;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = gridPosition.y + 9;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::NORMAL)
				{
					this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
				}
				else
				{
					if (shader)
						this->map[x][y][this->layer][k]->render(target, shader, playerPosition);
					else
						this->map[x][y][this->layer][k]->render(target);
				}
				if (show_collision)
				{
					if (this->map[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}

					if (this->map[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER)
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}

			}
		}
	}
}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition)
{
	while (!this->deferredRenderStack.empty())
	{
		if (shader)
		{
			this->deferredRenderStack.top()->render(target, shader, playerPosition);
		}
		else
		{
			this->deferredRenderStack.top()->render(target);
		}
		this->deferredRenderStack.pop();
	}
}


