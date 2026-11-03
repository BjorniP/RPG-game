#pragma once
#include "GameState.h"
#include"SettingsState.h"
#include"EditorState.h"
#include"Gui.h"
class MainMenuState :
    public State
{
private:
    //Creating the background
    sf::RectangleShape btnbackground;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    //To write over button(only for vision no function or linking)
    sf::Font font;
    //Changing the states with buttons in MainState
    std::map<std::string, gui::Button*>buttons;
    //Private functions
    void initVariables();
    void initFont();
    void initKeybinds();
    void initGui();
    void resetGui();
public:
    
    //Con/Destructors
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Public functions
    void updateInput(const float& dt);//reimplemented from base class State
    void updateButtons();//new
    void update(const float& dt);//reimplemented from base class State
    void renderButtons(sf::RenderTarget& target);//new
    void render(sf::RenderTarget* target = nullptr);//reimplemented from base class State

};

