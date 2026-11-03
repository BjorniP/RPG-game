#pragma once
#include "EditorMode.h"
class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class DefaultEditorMode :
    public EditorMode
{
private:
    bool tileAddLock;
    bool collision;
    short type;
    gui::TextureSelector* textureSelector;
    sf::IntRect textureRect;
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    int layer;

    void initVariables();
    void initGui();

public:
	DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~DefaultEditorMode();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

