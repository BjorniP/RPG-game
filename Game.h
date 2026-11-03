#pragma once
#include"MainMenuState.h"

class MainMenuState;

class Game
{
private:
	//Graphicssettings object
	StateData stateData;
	GraphicsSettings gfxSettings;
	//window stuff
	sf::RenderWindow* window;
	sf::Event sfEvent;

	float gridSize;
	//Timer/deltaTime
	sf::Clock dtClock;
	float dt;

	//States and supported keys
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	//Private functions
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();
public:
	//Cons/Destructors
	Game();
	virtual ~Game();

	//public functions
	void endApplication();
	void updateDT();
	void updateSfmlEvents();
	void update();
	void render();
	void run();
};

