#pragma once
#include"CharacterTab.h"

enum PLAYER_TABS {CHARACTER_TAB = 0,INVENTORY_TAB};
class PlayerGuiTabs
{
private:

	std::vector<Tab*> tabs;
	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

	sf::Clock keyTimer;
	float keyTimeMax;

	//functions

	void initTabs();
	void initKeyTime();
public:
	PlayerGuiTabs(sf::VideoMode& vm,sf::Font& font, Player& player);
	virtual ~PlayerGuiTabs();
	const bool getKeyTime();
	const bool tabsOpen();
	void toggleTab(const int tab_index);


	void update();
	void render(sf::RenderTarget& target);
};

