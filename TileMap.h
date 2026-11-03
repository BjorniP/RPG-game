#pragma once
#include"EnemySpawnerTile.h"
#include"RegularTile.h"
#include"EnemySystem.h"
#include"Weapon.h"

class TileMap
{
private:
	
	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	int layers;
	std::vector< std::vector < std::vector < std::vector<Tile*> > > >map;
	std::stack<Tile*> deferredRenderStack;

	std::string TextureFile;
	sf::Texture tileTextureSheet;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	//Debug
	sf::RectangleShape collisionBox;

	void clear();

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	TileMap(const std::string file_name);
	virtual~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;
	const int getTileLayers(const int x, const int y, const int layer) const;
	const bool tileEmpty(const int x, const int y, const int z) const;
	const bool checkType(const int x, const int y, const int z, const int type) const;
	//Functions
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);
	const sf::Vector2i& getMaxSizeWorldGrid() const;
	const sf::Vector2f& getMaxSizeWorldF() const;
	void addTiles(
		const int x, const int y, const int z,
		const sf::IntRect& texture_rect, const bool& collision, const short& type
	);
	void addTiles(
		const int x, const int y, const int z,
		const sf::IntRect& texture_rect, 
		const int enemy_type, const int enemy_amount, const int enemy_tts, const int enemy_md
	);
	void removeTiles(const int x, const int y, const int z,const int type = -1);
	void removeCollision(const int x, const int y, const int z, const int type = -1);


	void updateWorldBoundsCollision(Entity* entity, const float& dt);
	void updateTileCollision(Entity* entity, const float& dt);
	void updateTiles(Entity* entity, const float& dt,EnemySystem& enemy_system);

	void update(Entity* entity, const float& dt);
	
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition,sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f(), const bool show_collision = false);
	void renderDeferred(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());
};

