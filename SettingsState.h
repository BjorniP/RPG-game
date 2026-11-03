#pragma once
#include "State.h"
#include"Gui.h"
class SettingsState :
    public State
{
private:
    //Creating the background
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    //To write over button(only for vision no function or linking)
    sf::Font font;
    sf::Text optionsText;
    //Changing the states with buttons in MainState
    std::map<std::string, gui::Button*>buttons;
    std::map<std::string, gui::DropDownList*>dropDownlist;

    std::vector<sf::VideoMode> modes;
    //Private functions
    void initVariables();
    void initFont();
    void initKeybinds();
    void initGui();
    void resetGui();
public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //Public functions
    void updateInput(const float& dt);//reimplemented from base class State
    void updateGui(const float& dt);//new
    void update(const float& dt);//reimplemented from base class State
    void renderGui(sf::RenderTarget& target);//new
    void render(sf::RenderTarget* target = nullptr);//reimplemented from base class State
};

