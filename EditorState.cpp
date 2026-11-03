#include "stdafx.h"
#include "EditorState.h"

//Private functions
void EditorState::initVariables()
{
	this->cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytimer = &this->keytimer;
	this->editorStateData.keytimerMax = &this->keytimerMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
}

void EditorState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->Resolution.width),
			static_cast<float>(this->stateData->gfxSettings->Resolution.height)
		)
	);
	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->Resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->Resolution.height) / 2.f
	);
}


void EditorState::initFont()
{
	if (!this->font.loadFromFile("newFont.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULDNT LOAD FROM FILE");
	}
}


void EditorState::initKeybinds()
{
	std::ifstream ifs;
	ifs.open("editorstate_keybinds.txt");

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

void EditorState::initPauseMenu()
{
	sf::VideoMode& vm = this->stateData->gfxSettings->Resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->Resolution, font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "QUIT");
	this->pmenu->addButton("SAVE", gui::p2pY(46.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "SAVE");
	this->pmenu->addButton("LOAD", gui::p2pY(37.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "LOAD");
}

void EditorState::initButtons()
{

}

void EditorState::initGui()
{
	
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}

void EditorState::initTilemap()
{
	this->tileMap = new TileMap(this->stateData->GridSize, 75,75, "Tile/tilesheet3.png");
}

//Con/Destructors
EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->initFont();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTilemap();
	this->initGui();
	this->initModes();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;

	delete this->tileMap;

	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}

//Public functions

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pausedState();
		else
			this->unpasuedState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f,-this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP"))))
	{
		if (this->activeMode < this->modes.size() - 1)
		{
			this->activeMode++;
		}
		else
		{
			//std::cout << "ERROR::COULDNT MODE UP";
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
	{
		if (this->activeMode > 0)
		{
			this->activeMode--;
		}
		else
		{
			//std::cout << "ERROR::COULDNT MODE DONW";
		}
	}
	

	//Changing the texture Rect
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->getKeytime())
	{
		if (this->textureRect.left >= 0 || this->textureRect.left <= 700)
		{
			this->textureRect.left += 100;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->getKeytime())
	{
		if (this->textureRect.left >= 0 || this->textureRect.left <= 700)
		{
			this->textureRect.left -= 100;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->getKeytime())
	{
		if (this->textureRect.top >= 0 || this->textureRect.top <= 100)
		{
			this->textureRect.top += 100;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->getKeytime())
	{
		if (this->textureRect.top >= 0 || this->textureRect.top <= 100)
		{
			this->textureRect.top -= 100;
		}
	}*/
}

void EditorState::updateButtons()
{
	//All game buttons
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt)
{	
}

void EditorState::updatePauseMenuButtons()
{

	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("TileMapInfo.txt");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("TileMapInfo.txt");
}

void EditorState::updateModes(const float& dt)
{
	this->modes[this->activeMode]->update(dt);
}

void EditorState::update(const float& dt)
{
	this->updateMousePosition(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);
	if (!this->paused)
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

	//mos perdorim system("cls") sepse ben crash gjate debug
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	
}

void EditorState::renderModes(sf::RenderTarget& target)
{
	this->modes[this->activeMode]->render(target);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
    this->tileMap->render(*target, this->mousePosGrid,NULL,sf::Vector2f(),true);
	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderGui(*target);
	this->renderButtons(*target);
	this->renderModes(*target);

	if (paused)//render stuff during pause menu
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}
}