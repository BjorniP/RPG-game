#include "stdafx.h"
#include "CharacterTab.h"

void CharacterTab::initText()
{
	this->InfoText.setPosition(this->Back.getPosition().x + 20.f, this->Back.getPosition().y + 20.f);
	this->InfoText.setFont(this->font);
	this->InfoText.setCharacterSize(gui::calcCharSize(this->vm, 100));
	this->InfoText.setFillColor(sf::Color(200,200,200,240));
	this->InfoText.setString(this->player.toStringCharacterTab());
}

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player) :Tab(vm, font, player,false)
{
	this->Back.setFillColor(sf::Color(20, 20, 20, 240));
	this->Back.setSize(sf::Vector2f(gui::p2pX(50.f, this->vm), static_cast<float>(this->vm.height)));
	//text
	
	this->initText();
}

CharacterTab::~CharacterTab()
{
}

void CharacterTab::update()
{
	if (!this->hidden)
	{
		//Update the info
		this->InfoText.setString(this->player.toStringCharacterTab());
	}
}

void CharacterTab::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(Back);
		target.draw(InfoText);
	}
}
