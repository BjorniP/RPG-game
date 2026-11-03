#include "stdafx.h"
#include "Game.h"
//Static functions

//Initialzing private functions
void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
	this->gridSize = 64.f;
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("graphics.txt");
}

void Game::initWindow()
{
	if (this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow
		(
			this->gfxSettings.Resolution,
			this->gfxSettings.title,
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings
		);
	else
		this->window = new sf::RenderWindow
		(
			this->gfxSettings.Resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->gfxSettings.contextSettings);
	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs;
	ifs.open("key_support.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();

	//Debug
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.GridSize = this->gridSize;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

//Constructors/Destructors
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
	std::cout << "Game.cpp\n";
}

//Public functions
void Game::endApplication()
{
	std::cout << "Ending the application"<<std::endl;
}

void Game::updateDT()
{
	/*Update the delta time variable with the time it takes to update and render one frame*/
	this->dt = this->dtClock.restart().asSeconds();
	//std::cout << this->dt << "\n";
}

void Game::updateSfmlEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
			while(!this->states.empty())
			{
				delete this->states.top();
				this->states.pop();
			}
		}

	}
}

void Game::update()
{
	this->updateSfmlEvents();
	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);
			if (this->states.top()->getQuit())
			{
				delete this->states.top();
				this->states.pop();
			}
		}
		
	}
	//End of application
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty())
	{
		this->states.top()->render();
	}
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
        this->updateDT();
		this->update();
		this->render();
	}
}
