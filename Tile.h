#pragma once

enum TileTypes { DEFAULT = 0, BORDERS, NORMAL, ENEMYSPAWNER ,DAMAGING};
class Tile
{
private:

protected:
	sf::Sprite shape;
	bool collision;
	short type;
public:
	Tile();
	Tile(short type,int grid_x, int grid_y, float gridSizeF, const sf::Texture& tileTexture, const sf::IntRect& texture_rect,
		bool collision);
	virtual~Tile();

	//Accessors
	virtual const bool& getCollision() const;
	const short& getType() const;
	virtual const sf::Vector2f& getPosition() const;
	virtual const bool intersects(const sf::FloatRect bounds) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const bool removeCollision() = 0;
	virtual const std::string getAsString() const = 0;
	//Functions
	
	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f()) = 0;
};

