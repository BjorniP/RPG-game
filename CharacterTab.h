#pragma once
#include"Tab.h"
class CharacterTab : public Tab
{
private:
	//Character Tab
	sf::RectangleShape Back;
	sf::Text InfoText;
	void initText();
public:
	CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~CharacterTab();

	void update();
	void render(sf::RenderTarget& target);
};

