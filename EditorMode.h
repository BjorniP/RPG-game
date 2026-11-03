#pragma once
#include"State.h"
#include"Tile.h"
#include"TileMap.h"
#include"Gui.h"
class State;
class StateData;
class TileMap;
class Tile;
class EditorStateData
{
public:
    EditorStateData() {};

    //Variables
    sf::View* view;
    sf::Font* font;
    float* keytimer;
    float* keytimerMax;
    sf::Vector2i* mousePosScreen;
    sf::Vector2i* mousePosWindow;
    sf::Vector2f* mousePosView;
    sf::Vector2i* mousePosGrid;
    std::map < std::string, int >* keybinds;
};
class EditorMode
{
protected:
	StateData* stateData;
    EditorStateData* editorStateData;
    TileMap* tileMap;
public:
	EditorMode(StateData* state_data,TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EditorMode();

	//functions
    const bool getKeytime();
    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual void update(const float& dt)=0;
    virtual void renderGui(sf::RenderTarget& target)=0;
    virtual void render(sf::RenderTarget& target)=0;

};

