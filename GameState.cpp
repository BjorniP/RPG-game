#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->Resolution.width,
		this->stateData->gfxSettings->Resolution.height
	);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0,
			this->stateData->gfxSettings->Resolution.width,
		    this->stateData->gfxSettings->Resolution.height
		    )
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->Resolution.width/2),
			static_cast<float>(this->stateData->gfxSettings->Resolution.height/2)
		)
	);
	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->Resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->Resolution.height) / 2.f
	);
}

//Private functions
void GameState::initKeybinds()
{
	std::ifstream ifs;
	ifs.open("gamestate_keybinds.txt");

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

void GameState::initFont()
{
	if (!this->font.loadFromFile("newFont.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULDNT LOAD FROM FILE");
	}
}

void GameState::initTexture()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Player/PLAYER_SHEET2.png"))
	{
		throw("COULDNT LOAD THE PLAYER_IDLE TEXTURE::ERROR");
	}
	else
	{
		this->textures["PLAYER_SHEET"].setSmooth(true);
		this->textures["PLAYER_SHEET"].setRepeated(true);
	}

	if (!this->textures["RAT1_SHEET"].loadFromFile("Resources/Enemy/rat1_60x64.png"))
	{
		throw("COULDNT LOAD THE PLAYER_IDLE TEXTURE::ERROR");
	}
}

void GameState::initPauseMenu()
{
	sf::VideoMode& vm = this->stateData->gfxSettings->Resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->Resolution, font);

	this->pmenu->addButton("QUIT",gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),gui::calcCharSize(vm), "QUIT");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "COULDNT LOAD SHADER::GAMESTATE" << "\n";
	}
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGUi()
{
	this->PlayerGui = new playerGui(this->player, this->stateData->gfxSettings->Resolution);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void GameState::initTextTagSystem()
{
	this->tts = new TextTagSystem("newFont.ttf");
}

void GameState::initTilemap()
{
	this->tileMap = new TileMap("TileMapInfo.txt");
}

void GameState::initKeyTime()
{
	this->keyTimeMax = 0.5f;
	this->keyTimer.restart();
}

void GameState::initDebugText()
{
	this->debugText.setFont(this->font);
	this->debugText.setFillColor(sf::Color::White);
	this->debugText.setCharacterSize(16);
	this->debugText.setPosition(15.f, this->window->getSize().y / 2.f);
}
//Cosn/Destructors
GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFont();
	this->initTexture();
	this->initPauseMenu();
	this->initShaders();
	this->initKeyTime();
	this->initDebugText();
	this->initPlayers();
	this->initPlayerGUi();
	this->initEnemySystem();
	this->initTextTagSystem();
	this->initTilemap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->PlayerGui;
	delete this->enemySystem;
	delete this->tileMap;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}

	delete this->tts;
}

//Public functions reimplemented from State parent-class

const bool GameState::getKeyTimer()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}
	return false;
}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->Resolution.width / 2)) / 10.f)
		, std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->Resolution.height / 2)) / 10.f)
	);
	

	if (this->tileMap->getMaxSizeWorldF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeWorldF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeWorldF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}
	 
	if (this->tileMap->getMaxSizeWorldF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeWorldF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeWorldF().y - this->view.getSize().y / 2.f);
		}
	}
	
	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->GridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->GridSize);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pausedState();
		else
			this->unpasuedState();
	}
}

void GameState::updatePauseMenuButtons()
{

	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	for (auto *i : this->activeEnemies)
	{
		this->tileMap->updateWorldBoundsCollision(i, dt);
		this->tileMap->updateTileCollision(i, dt);
	}
	
	this->tileMap->updateTiles(this->player, dt,*this->enemySystem);
	if (this->player->getAttributeComponent()->level >= 3)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTimer())
		{
			this->tileMap->removeCollision(this->mousePosGrid.x, this->mousePosGrid.y, 0, TileTypes::BORDERS);
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->move(-1, 0, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->move(1, 0, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0, -1, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0, 1, dt);
	}
}

void GameState::updatePlayerGui(const float& dt)
{
	this->PlayerGui->update(dt,this->mousePosWindow);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_PLAYER_TAB"))) && this->getKeyTimer())
	{
		this->PlayerGui->toggleCharacterTab();
	}
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePosView,this->view);
}

void GameState::updateCombatAndEnemies(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->getWeapon()->getAttackTimer())
		this->player->setInitAttack(true);
	unsigned index = 0;
	for (auto* enemy : this->activeEnemies)
	{
		enemy->update(dt, this->mousePosView,this->view);
		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTileCollision(enemy, dt);
		
		   this->updateCombat(enemy,index, dt);
		if(enemy->isDead())
		{
			this->player->gainExp(enemy->gainExp());
			this->tts->addTextTag(EXPERIENCE_TAG,
				this->player->getPosition().x-40.f, this->player->getPosition().y - 30.f, static_cast<int>(enemy->gainExp()), "+", "EXP");
			this->enemySystem->removeEnemy(index);
			continue;
		}
		else if (enemy->getDespawnTimerDone())
		{
			this->enemySystem->removeEnemy(index);
			continue;
		}
		++index;
	}
	this->player->setInitAttack(false);
	//this->activeEnemies.push_back(new Rat(200.f, 100.f, this->textures["RAT1_SHEET"]));
}

void GameState::updateCombat(Enemy* enemy,const int index, const float& dt)
{
	if (player->getInitAttack() && enemy->getGlobalBounds().contains(this->mousePosView) &&
		enemy->getSpriteDistance(*this->player) < this->player->getWeapon()->getRange() && enemy->getDamageTimerDone())
	{
		int dmg = static_cast<int>(this->player->getDamage());
		enemy->loseHp(dmg);
		enemy->resetDamageTimer();
		this->tts->addTextTag(DEFAULT_TAG, enemy->getPosition().x, enemy->getPosition().y, dmg, "", "");
	}

	if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
	{
		int dmg = enemy->getAttributeComp()->damageMax;
		this->player->loseHP(dmg);
		this->tts->addTextTag(NEGATIVE_TAG,
			player->getPosition().x - 30.f, player->getPosition().y,
			dmg, "-", "HP");
	}
}

void GameState::updateDebugText(const float& dt)
{
	std::stringstream ss;
	ss << "Mouse Pos View: " << this->mousePosView.x << "  " << this->mousePosView.y << "\n"
		<< "Active Enemies: " << this->activeEnemies.size() << "\n";
	this->debugText.setString(ss.str());
}

void GameState::update(const float& dt)
{
	this->updateMousePosition(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateDebugText(dt);

	if (!paused)//update if is not paused
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		this->updateTileMap(dt);
		this->updatePlayer(dt);
		this->updatePlayerGui(dt);
		this->updateCombatAndEnemies(dt);
		this->tts->update(dt);
	}
	else//stop updating during pause
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
	
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(
		this->renderTexture, this->viewGridPosition,
		&this->core_shader, this->player->getCenter(), false);

	for (auto* enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}
    this->player->render(this->renderTexture,&this->core_shader,this->player->getCenter(),false);
	this->tileMap->renderDeferred(this->renderTexture,&this->core_shader,this->player->getCenter());
	this->tts->render(this->renderTexture);
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->PlayerGui->render(this->renderTexture);
	
	if (paused)//render stuff during pause menu
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	this->renderTexture.draw(this->debugText);
	//FINAL RENDER
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
