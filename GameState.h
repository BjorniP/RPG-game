#pragma once
#include "State.h"
#include"PauseMenu.h"
#include"TileMap.h"
#include"playerGui.h"
#include"Sword.h"
#include"Bow.h"
#include"TextTagSystem.h"

class GameState :
    public State
{
private:
    //View(camera variables)
    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Shader core_shader;

    sf::Clock keyTimer;
    float keyTimeMax;

    sf::Text debugText;
    //Creating an objecting in private so only this class can access the functions and variables(data) of that class
    Player* player;
    playerGui* PlayerGui;
    PauseMenu* pmenu;
    sf::Font font;
    std::vector<Enemy*>activeEnemies;
    EnemySystem* enemySystem;
    TileMap* tileMap;
    

    //System
    TextTagSystem* tts;
    //Private functions
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFont();
    void initTexture();
    void initPauseMenu();
    void initShaders();
    void initKeyTime();
    void initDebugText();
    void initPlayers();
    void initPlayerGUi();
    void initEnemySystem();
    void initTextTagSystem();
    void initTilemap();
public:
    //Cons/Destructors
    GameState(StateData* state_data);
    virtual ~GameState();

    //Public functions reimplemented from State parent-class
    const bool getKeyTimer();

    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGui(const float& dt);
    void updatePlayer(const float& dt);
    void updateCombatAndEnemies(const float& dt);
    void updateCombat(Enemy* enemy, const int index, const float& dt);
    void updateDebugText(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

