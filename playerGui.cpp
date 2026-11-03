#include "stdafx.h"
#include "playerGui.h"

void playerGui::initFont()
{
	if (!this->font.loadFromFile("newFont.ttf"))
	{
		throw("ERROR::playerGui::COULDNT LOAD FROM FILE");
	}
}
void playerGui::initKeyTimer()
{
	this->keyTimeMax = 0.4f;
	this->keyTimer.restart();
}

void playerGui::initLevelBar()
{
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.9f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(20, 250, 20, 200));
	this->levelBarBack.setPosition(x, y);
		  
	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 150));
	this->levelBarText.setOutlineThickness(2.f);
	this->levelBarText.setPosition(this->levelBarBack.getPosition().x + gui::p2pX(0.53f, this->vm),
		this->levelBarBack.getPosition().y + gui::p2pY(0.5f, this->vm));
}

void playerGui::initSkills()
{
	this->vitalityBar = new gui::ProgressBar(12.f, 3.0f, 10.f, 1.5f, sf::Color(255, 100, 100, 200), 0, this->vm);
	this->strengthBar = new gui::ProgressBar(12.f, 4.6f, 10.f, 1.5f, sf::Color(100, 100, 250, 230), 0, this->vm);
	this->agilityBar = new gui::ProgressBar(12.f, 6.2f, 10.f, 1.5f, sf::Color(150, 200, 150, 200), 0, this->vm);
	this->dexterityBar = new gui::ProgressBar(12.f, 7.8f, 10.f, 1.5f, sf::Color(150, 250, 100, 150), 0, this->vm);
	this->intelligenceBar = new gui::ProgressBar(12.f, 9.4f, 10.f, 1.5f, sf::Color(150, 150, 250, 200), 0, this->vm);
}

void playerGui::initIncreaseSkillButtons()
{
	this->addPoint_toVitality = new gui::Circleshape(23.f, 3.0f, 0.6f, 100, this->vm, &this->font);
	this->addPoint_toStrength = new gui::Circleshape(23.f, 4.7f, 0.6f, 100, this->vm, &this->font);
	this->addPoint_toAgility = new gui::Circleshape(23.f, 6.3f, 0.6f, 100, this->vm, &this->font);
	this->addPoint_toDexterity = new gui::Circleshape(23.f, 7.9f, 0.6f, 100, this->vm, &this->font);
	this->addPoint_toIntelligence = new gui::Circleshape(23.f, 9.5f, 0.6f, 100, this->vm, &this->font);
}

void playerGui::initHpBar()
{

	this->hpBar = new gui::ProgressBar(1.f, 5.6f, 10.4f, 1.9f,
		sf::Color::Red, 180, this->vm, &this->font);
}

void playerGui::initExpBar()
{
	this->expBar = new gui::ProgressBar(1.f, 8.3f, 10.4f, 2.8f,
		sf::Color::Blue, 220, this->vm, &this->font);
}

void playerGui::initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player)
{
	this->playerTabs = new PlayerGuiTabs(vm, font, player);
}

playerGui::playerGui(Player* player, sf::VideoMode& vm)
	:vm(vm)
{
	this->player = player;
	this->initKeyTimer();
	this->initFont();
	this->initLevelBar();
	this->initSkills();
	this->initHpBar();
	this->initExpBar();
	this->initIncreaseSkillButtons();
	this->initPlayerTabs(vm,font,*player);
}

playerGui::~playerGui()
{
	delete this->hpBar;
	delete this->expBar;
	delete this->playerTabs;
	delete this->intelligenceBar;
	delete this->vitalityBar;
	delete this->strengthBar;
	delete this->agilityBar;
	delete this->dexterityBar;
	delete this->addPoint_toVitality;
	delete this->addPoint_toStrength;
	delete this->addPoint_toAgility;
	delete this->addPoint_toDexterity;
	delete this->addPoint_toIntelligence;
}

const bool playerGui::getKeyTimer()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}
	return false;
}



const bool playerGui::getTabsOpen() const
{
	return this->playerTabs->tabsOpen();
}

void playerGui::toggleCharacterTab()
{
	this->playerTabs->toggleTab(PLAYER_TABS::CHARACTER_TAB);
}

void playerGui::controll()
{
	if (this->addPoint_toVitality)
	{
		if(this->addPoint_toVitality== NULL)
		delete this->addPoint_toVitality;
	}
	if (this->addPoint_toStrength)
	{
		if (this->addPoint_toStrength == NULL)
			delete this->addPoint_toStrength;
	}
	if (this->addPoint_toAgility)
	{
		if (this->addPoint_toAgility == NULL)
			delete this->addPoint_toAgility;
	}
	if (this->addPoint_toDexterity)
	{
		if (this->addPoint_toDexterity == NULL)
			delete this->addPoint_toDexterity;
	}
	if (this->addPoint_toIntelligence)
	{
		if (this->addPoint_toIntelligence == NULL)
			delete this->addPoint_toIntelligence;
	}	
}

void playerGui::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void playerGui::updateHpBar()
{
	this->hpBar->update(this->player->getAttributeComponent()->hp,this->player->getAttributeComponent()->hpMax);
}

void playerGui::updateExpBar()
{
	this->expBar->update(this->player->getAttributeComponent()->exp, this->player->getAttributeComponent()->expNext);
}

void playerGui::updateSkillBars()
{
	this->vitalityBar->update(this->player->getAttributeComponent()->vitality, this->player->getAttributeComponent()->MaximumSkill);
	this->strengthBar->update(this->player->getAttributeComponent()->strength, this->player->getAttributeComponent()->MaximumSkill);
	this->agilityBar->update(this->player->getAttributeComponent()->agility, this->player->getAttributeComponent()->MaximumSkill);
	this->dexterityBar->update(this->player->getAttributeComponent()->dexterity, this->player->getAttributeComponent()->MaximumSkill);
	this->intelligenceBar->update(this->player->getAttributeComponent()->intelligence, this->player->getAttributeComponent()->MaximumSkill);
}

void playerGui::updateCircleButtons(const sf::Vector2i& mousePosWindow)
{
	if (!this->player->getAttributeComponent()->VitalityMax())
	{
		if (this->addPoint_toVitality->update(mousePosWindow) && this->getKeyTimer())
		{
			this->player->getAttributeComponent()->vitality++;
			this->player->getAttributeComponent()->removeAttributePoints();
		}
	}
	if (!this->player->getAttributeComponent()->AgilityMax())
	{
		if (this->addPoint_toAgility->update(mousePosWindow) && this->getKeyTimer())
		{
			this->player->getAttributeComponent()->agility++;
			this->player->getAttributeComponent()->removeAttributePoints();
		}
	}
	
	if (!this->player->getAttributeComponent()->DexterityMax())
	{
		if (this->addPoint_toDexterity->update(mousePosWindow) && this->getKeyTimer())
		{
			this->player->getAttributeComponent()->dexterity++;
			this->player->getAttributeComponent()->removeAttributePoints();
		}
	}
	if (!this->player->getAttributeComponent()->IntelligenceMax())
	{
		if (this->addPoint_toIntelligence->update(mousePosWindow) && this->getKeyTimer())
		{
			this->player->getAttributeComponent()->intelligence++;
			this->player->getAttributeComponent()->removeAttributePoints();
		}
	}
	if (!this->player->getAttributeComponent()->StrengthMax())
	{
		if (this->addPoint_toStrength->update(mousePosWindow) && this->getKeyTimer())
		{
			this->player->getAttributeComponent()->strength++;
			this->player->getAttributeComponent()->removeAttributePoints();
		}
	}
	
}

void playerGui::updatePlayerTabs()
{
	this->playerTabs->update();
}

void playerGui::update(const float& dt, const sf::Vector2i& mousePosWindow)
{
	this->updateHpBar();
	this->updateExpBar();
	this->updateLevelBar();
	if (this->player->getAttributeComponent()->attributePoints != 0)
	{
		this->updateSkillBars();
		this->updateCircleButtons(mousePosWindow);
	}
	this->updatePlayerTabs();
}

void playerGui::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void playerGui::renderHpBar(sf::RenderTarget& target)
{
	this->hpBar->render(target);
}


void playerGui::renderExpBar(sf::RenderTarget& target)
{
	this->expBar->render(target);
}

void playerGui::renderSkillBars(sf::RenderTarget& target)
{
	this->vitalityBar->render(target);
	this->strengthBar->render(target);
	this->agilityBar->render(target);
	this->dexterityBar->render(target);
	this->intelligenceBar->render(target);
}

void playerGui::renderCircleButtons(sf::RenderTarget& target)
{
	if (!this->player->getAttributeComponent()->VitalityMax())
	{
		this->addPoint_toVitality->render(target);
	}    
	else
	{
		this->addPoint_toVitality = NULL;
		this->controll();
	}
	if (!this->player->getAttributeComponent()->AgilityMax())
	{
		this->addPoint_toAgility->render(target);
	}  
	else
	{
		this->addPoint_toAgility = NULL;
		this->controll();
	}
	if (!this->player->getAttributeComponent()->DexterityMax())
	{
		this->addPoint_toDexterity->render(target);
	}
	else
	{
		this->addPoint_toDexterity = NULL;
		this->controll();
	}
	if (!this->player->getAttributeComponent()->IntelligenceMax())
	{
		this->addPoint_toIntelligence->render(target);
	}
	else
	{
		this->addPoint_toIntelligence = NULL;
		this->controll();
	}
	if (!this->player->getAttributeComponent()->StrengthMax())
	{
		this->addPoint_toStrength->render(target);
	}
	else
	{
		this->addPoint_toStrength = NULL;
		this->controll();
	}
}

void playerGui::renderPlayerTabs(sf::RenderTarget& target)
{
	this->playerTabs->render(target);
}

void playerGui::render(sf::RenderTarget& target)
{
	this->renderLevelBar(target);
	this->renderHpBar(target);
	this->renderExpBar(target);
	if (this->player->getAttributeComponent()->attributePoints != 0)
	{
		this->renderSkillBars(target);
		this->renderCircleButtons(target);
	}
	this->renderPlayerTabs(target);
}
