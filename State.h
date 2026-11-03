#pragma once
#include"Player.h"
#include"GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {};

	float GridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map < std::string,int > * supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:

protected://all this variables and functions can be heritaged to child classes
	
	StateData* stateData;

	//Pointers that point in window in Game.cpp
	sf::RenderWindow* window;
	std::stack<State*>* states;
	
	//Pointers that point at supported keys at main
	std::map<std::string, int>* supportedKeys;
	
	//Creating the same button but with new unique key and with the position of the main keys in Game.cpp
	std::map<std::string, int> keybinds;
	
	//if quit==true we exit game
	bool quit;
	bool paused;

	//timer for button press in pause menu
	float keytimer;
	float keytimerMax;

	float gridSize;
	//Position for MouseInput relative to window/screen and view
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;
	//Resources
	std::map<std::string,sf::Texture> textures;

	//Pure virtual protected function
	virtual void initKeybinds() = 0;

public:
	
	//Con/Destructors
	State(StateData* state_data);
	virtual ~State();
	
	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();
	
	//Public functions
	virtual void updateMousePosition(sf::View* view = NULL);
	virtual void updateKeytime(const float& dt);
	void endState();
	void pausedState();
	void unpasuedState();
	
	//Pure virtual public functions
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

