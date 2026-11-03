#include"stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

//Private functions
void SettingsState::initFont()
{
	if (!this->font.loadFromFile("newFont.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULDNT LOAD FROM FILE");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
	sf::VideoMode& vm = this->stateData->gfxSettings->Resolution;

	//init background
	this->background.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->backgroundTexture.loadFromFile("Resources/Background/bg1.png");
	this->background.setTexture(&this->backgroundTexture);

	//buttons
	this->buttons["BACK"] = new gui::Button(gui::p2pX(72.f, vm), gui::p2pY(81.5f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f,vm), &this->font, "Back", gui::calcCharSize(vm),
		sf::Color(150, 120, 120, 220), sf::Color(200, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = new gui::Button(gui::p2pX(60.f, vm), gui::p2pY(81.5f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), &this->font, "Apply", gui::calcCharSize(vm),
		sf::Color(150, 120, 120, 220), sf::Color(200, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropDownlist["Resolution"] = new gui::DropDownList
	(gui::p2pX(42.f, vm), gui::p2pY(42.f, vm), gui::p2pX(10.4f, vm), gui::p2pY(4.5f, vm), gui::calcCharSize(vm, 90),
		font, modes_str.data(), static_cast<unsigned short>(modes_str.size()));


	//init text
	this->optionsText.setFont(font);
	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f,vm),gui::p2pY(41.7f,vm)));
	this->optionsText.setCharacterSize(gui::calcCharSize(vm, 80));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
	);
}

void SettingsState::resetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto it2 = this->dropDownlist.begin();
	for (it2 = this->dropDownlist.begin(); it2 != this->dropDownlist.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownlist.clear();

	this->initGui();
}


SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFont();
	this->initKeybinds();
	this->initGui();
	
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownlist.begin();
	for (it2 = this->dropDownlist.begin(); it2 != this->dropDownlist.end(); ++it2)
	{
		delete it2->second;
	}
	
}

//Public functions

void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	//Update all gui elements in the state and handle their funcionality
	//Buttons
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}
	//Button functionalities
	//Quit the settings state
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		this->stateData->gfxSettings->Resolution = this->modes[this->dropDownlist["Resolution"]->getActiveElementID()];
		this->window->create(this->stateData->gfxSettings->Resolution, this->stateData->gfxSettings->title, sf::Style::Default);
		this->resetGui();
	}
	//Dropdownlist lists
	for (auto& i : this->dropDownlist)
	{
		i.second->update(this->mousePosWindow, dt);
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	//mos perdorim system("cls") sepse ben crash gjate debug
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
	this->updateGui(dt);

	//this->ddl->update(this->mousePosView, dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
	for (auto& i : this->dropDownlist)
	{
		i.second->render(target);
	}
	target.draw(this->optionsText);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);

	this->renderGui(*target);
	
	//For debugging 

	//Debug Mouse coordinates relative to the world coordinates(of the game)/View Mode
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);

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