#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables()
{
}


//Private functions
void MainMenuState::initFont()
{
	if (!this->font.loadFromFile("newFont.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULDNT LOAD FROM FILE");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs;
	ifs.open("mainmenustate_keybinds.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void MainMenuState::initGui()
{
	sf::VideoMode& vm = this->stateData->gfxSettings->Resolution;
	this->background.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->backgroundTexture.loadFromFile("Resources/Background/bg2.png");
	this->background.setTexture(&this->backgroundTexture);

	this->btnbackground.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(vm.width / 5),
			static_cast<float>(vm.height)
		)
	);
	this->btnbackground.setPosition(gui::p2pX(11.5, vm), 0.f);
	this->btnbackground.setFillColor(sf::Color(10,10,10,220));

	//Buttons
	this->buttons["Game_State"] = new gui::Button
	(
	   gui::p2pX(15.6f, vm), gui::p2pY(30.f, vm), gui::p2pX(13.1f, vm), gui::p2pY(6.f, vm),
	   &this->font, "New Game", gui::calcCharSize(vm),
	   sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
	   sf::Color(70,70,70,0), sf::Color(150,150,150,0),sf::Color(20,20,20,0)
    );
	this->buttons["SETTINGS_STATE"] = new gui::Button
	(
		gui::p2pX(15.6f, vm), gui::p2pY(40.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Settings", gui::calcCharSize(vm),
		sf::Color(120, 120, 150, 200), sf::Color(120, 120, 200, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0),sf::Color(150, 150, 150, 0),sf::Color(20, 20, 20, 0)
	);
	this->buttons["EDITOR_STATE"] = new gui::Button
	(
		gui::p2pX(15.6f, vm), gui::p2pY(50.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Editor", gui::calcCharSize(vm),
		sf::Color(120, 150, 120, 200), sf::Color(120, 200, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0),sf::Color(150, 150, 150, 0),sf::Color(20, 20, 20, 0)
	);
	this->buttons["Exit_State"] = new gui::Button
	(
		gui::p2pX(15.6f, vm), gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(150, 120, 120, 220), sf::Color(200, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 70, 0),sf::Color(150, 150, 150, 0),sf::Color(20, 20, 20, 0)
	);
}

void MainMenuState::resetGui()
{

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();
	this->initGui();
}

//Con/Destructors
MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFont();
	this->initKeybinds();
	this->initGui();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	std::cout << "MainMenuState.cpp\n";
}

//Public functions

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	//All game buttons
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}
	//Quit button
	if (this->buttons["Exit_State"]->isPressed())
	{
		this->endState();
	}
	//Initialize the game
	if (this->buttons["Game_State"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}
	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}
	//Editor state
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	//mos perdorim system("cls") sepse ben crash gjate debug
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
	
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->btnbackground);
	this->renderButtons(*target);

	
	
	//For debugging 

	//Debug Mouse coordinates relative to the world coordinates(of the game)/View Mode
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/

	//Debug Mouse coordinates relative to the desktop of PC
	/*sf::Text mouseText1;
	mouseText1.setPosition(this->mousePosView.x, this->mousePosView.y + 100.f);
	mouseText1.setFont(this->font);
	mouseText1.setCharacterSize(12);
	std::stringstream ss1;
	ss1 << this->mousePosScreen.x << " " << this->mousePosScreen.y;
	mouseText1.setString(ss1.str());
	target->draw(mouseText1);*/

	//Debug Mouse coordinates relative to the window
	/*sf::Text mouseText2;
	mouseText2.setPosition(this->mousePosView.x - 50.f, this->mousePosView.y - 150.f);
	mouseText2.setFont(this->font);
	mouseText2.setCharacterSize(12);
	std::stringstream ss2;
	ss2 << this->mousePosWindow.x << " " << this->mousePosWindow.y;
	mouseText2.setString(ss2.str());
	target->draw(mouseText2);*/
}