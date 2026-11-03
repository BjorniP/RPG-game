#pragma once
#include"PlayerGuiTabs.h"

class playerGui
{
private:
	Player* player;
	sf::VideoMode& vm;
	sf::Font font;
	//LevelBar
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;

	//ExpBar
	gui::ProgressBar* expBar;

	//Hp bar
	gui::ProgressBar* hpBar;
	gui::ProgressBar* vitalityBar;
	gui::ProgressBar* strengthBar;
	gui::ProgressBar* agilityBar;
	gui::ProgressBar* dexterityBar;
	gui::ProgressBar* intelligenceBar;

	gui::Circleshape* addPoint_toVitality;
	gui::Circleshape* addPoint_toStrength;
	gui::Circleshape* addPoint_toAgility;
	gui::Circleshape* addPoint_toDexterity;
	gui::Circleshape* addPoint_toIntelligence;


	PlayerGuiTabs* playerTabs;
	float keyTimeMax;
	sf::Clock keyTimer;
	void initFont();
	void initKeyTimer();
	void initLevelBar();
	void initSkills();
	void initIncreaseSkillButtons();
	void initHpBar();
	void initExpBar();
	void initPlayerTabs(sf::VideoMode &vm,sf::Font& font,Player& player);
	
public:
	playerGui(Player* player, sf::VideoMode& vm);
	virtual ~playerGui();

	const bool getKeyTimer();

	const bool getTabsOpen() const;
	void toggleCharacterTab();

	void controll();
	void updateLevelBar();
	void updateHpBar();
	void updateExpBar();
	void updateSkillBars();
	void updateCircleButtons(const sf::Vector2i& mousePosWindow);
	void updatePlayerTabs();
	void update(const float& dt,const sf::Vector2i& mousePosWindow);
	
	void renderLevelBar(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderSkillBars(sf::RenderTarget& target);
	void renderCircleButtons(sf::RenderTarget& target);
	void renderPlayerTabs(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

