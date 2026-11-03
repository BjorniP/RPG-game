#pragma once
#include "State.h"
#include"Gui.h"
#include"PauseMenu.h"
#include"TileMap.h"
#include"EditorModes.h"

class State;
class Gui;
class PauseMenu;
class TileMap;
class DefaultEditorMode;
class EditorStateData;

enum EditorModes { DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE };

class EditorState :
    public State
{
private:
    EditorStateData editorStateData;

    sf::View view;
    float cameraSpeed;
    sf::Font font;
    //Changing the states with buttons in MainState
    std::map<std::string, gui::Button*>buttons;
    std::vector<EditorMode*> modes;
    
    //Pausing this state
    PauseMenu* pmenu;
    //Tile map in editor state
    TileMap* tileMap;


    unsigned activeMode;
    //Private functions
    void initVariables();
    void initEditorStateData();
    void initView();
    void initFont();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initTilemap();
    void initGui();
    void initModes();
public:

    //Con/Destructors
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Public functions
    void updateInput(const float& dt);//reimplemented from base class State
    void updateEditorInput(const float& dt);
    void updateButtons();//new
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void updateModes(const float& dt);
    void update(const float& dt);//reimplemented from base class State
    void renderButtons(sf::RenderTarget& target);//new
    void renderGui(sf::RenderTarget& target);
    void renderModes(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);//reimplemented from base class State

};

