#include "stdafx.h"  
#include "Gui.h"

const float gui::p2pX(const float perc, sf::VideoMode& vm)
{
	//return a float percentage of the pixels relative to the resolution in the x-axis
	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, sf::VideoMode& vm)
{
	//return a float percentage of the pixels relative to the resolution in the y-axis
	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const float gui::p2p(const float perc, sf::VideoMode& vm)
{
	return std::floor(static_cast<float>((vm.height + vm.width)/2.f) * (perc / 100.f));
}

const unsigned gui::calcCharSize(sf::VideoMode& vm, const unsigned modifier)
{
	//calc the text size depending on the resolution and the constant
	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

//Class button
//Cons/Destructors
gui::Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text
	, unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color
	, sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color,
	sf::Color outline_idle_Color, sf::Color outline_hover_Color , sf::Color outline_active_Color
	, short unsigned id)
{
	this->id = id;

	this->buttonState = BTN_IDLE;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_Color);
	this->shape.setOutlineThickness(2.f);
	this->shape.setOutlineColor(outline_idle_Color);

	this->font = font;
	this->text.setFont(*this->font);

	this->text.setString(text);
	this->text.setCharacterSize(character_size);
	this->text.setFillColor(text_idle_color);
	this->text.setPosition
	(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_Color;
	this->hoverColor = hover_Color;
	this->activeColor = active_Color;

	this->outlineIdleColor = outline_idle_Color;
	this->outlineHoverColor = outline_hover_Color;
	this->outlineActiveColor = outline_active_Color;
}

gui::Button::~Button()
{
}

//Accessories
//const bool& gui::Button::isPressed1() const
//{
//	if (this->buttonState == BTN_PRESSED)
//		return true;
//	return false;
//}

const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED)
		return true;
	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Public functions
void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/
	//IDLE
	this->buttonState = BTN_IDLE;
    //HOVER
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;
		//PRESSED
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_PRESSED;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Green);
		this->text.setFillColor(sf::Color::Green);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//Class DropDownBox=========================================================


gui::DropDownList::DropDownList(float x, float y, float width, float height,int CharSize,
	sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index)
	:font(font),showlist(false),keytimerMax(1.f),keytimer(0.f)
{
	this->activeElement = new Button(
		x, y, width, height, &this->font, list[default_index],CharSize,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(150,80,80,150),sf::Color(200,100,100,200),sf::Color(50,50,50,200)
		);

	//nrOfElements= sizeof(list)/sizeof(std::string)
	for (unsigned short i = 0; i < nrOfElements; i++)
	{
		this->list.push_back
		(
			new gui::Button
			(
				x, y + ((i + 1) * height), width, height, &this->font, list[i], CharSize,
				sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(150, 80, 80, 150), sf::Color(200, 100, 100, 200), sf::Color(50, 50, 50, 200),i
			)
		);
	}
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	/*for (auto*& i : this->list)
		delete i;*/
	for (size_t a = 0; a < this->list.size(); a++)
	{
		delete this->list[a];
	}
}

//Accessories
const bool gui::DropDownList::getKeytimer()
{
	if (this->keytimer >= this->keytimerMax)
	{
		this->keytimer = 0.f;
		return true;
	}
	return false;
}

void gui::DropDownList::updateKeytimer(const float &dt)
{
	if (this->keytimer < this->keytimerMax)
	{
		this->keytimer += 10.f * dt;
	}
}

const short unsigned& gui::DropDownList::getActiveElementID() const
{
	return this->activeElement->getId();
}

//Public functions
void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytimer(dt);

	this->activeElement->update(mousePosWindow);

	if (this->activeElement->isPressed() && this->getKeytimer())
	{
		if (this->showlist)
			this->showlist = false;
		else
			this->showlist = true;
	}

	if (this->showlist)
	{
		for (auto& i : this->list)
		{
			i->update(mousePosWindow);
			if (i->isPressed() && this->getKeytimer())
			{
				this->showlist = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showlist)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}


//class TextureSelector ================================================================

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridsize,
	const sf::Texture* texture_sheet, sf::Font& font, std::string text) : keytimer(0.f), keytimerMax(1.f)
{
	
	this->gridSize = gridsize;
	float offset = this->gridSize;
	this->active = false;
	this->hidden = false;
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);

	this->sheet.setPosition(x + offset, y);
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect
		(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect
		(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridsize, gridsize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(gridsize);
	this->textureRect.height = static_cast<int>(gridsize);

	this->hide_btn = new gui::Button(x, y, 50.f, 50.f, &font, text, 24,
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 200),
		sf::Color(200, 200, 200, 200), sf::Color(200, 200, 200, 200), sf::Color(200, 200, 200, 200));
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hide_btn;
}

//Accessories
const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool gui::TextureSelector::getKeytimer()
{
	if (this->keytimer >= this->keytimerMax)
	{
		this->keytimer = 0.f;
		return true;
	}
	return false;
}


//Functions
void gui::TextureSelector::updateKeytimer(const float& dt)
{
	if (this->keytimer < this->keytimerMax)
	{
		this->keytimer += 10.f * dt;
	}
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytimer(dt);

	this->hide_btn->update(mousePosWindow);
	if (this->hide_btn->isPressed() && this->getKeytimer())
	{
		if (hidden)
		{
			this->hidden = false;
		}
		else
			this->hidden = true;
	}

	if (!hidden)
	{
		this->active = false;
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->active = true;
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
	
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	this->hide_btn->render(target);

	if(!hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);
		if (this->active)
			target.draw(this->selector);
	}

}

//ProgressBar class ==================================================================================================
gui::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height,
	sf::Color inner_color, unsigned character_size, sf::VideoMode& vm, sf::Font* font)
{
	float width = gui::p2pX(_width, vm);
	float height = gui::p2pY(_height, vm);
	float x = gui::p2pX(_x, vm);
	float y = gui::p2pY(_y, vm);
	this->BarMaxWidth = width;

	this->BarBack.setSize(sf::Vector2f(width, height));
	this->BarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->BarBack.setPosition(x, y);

	this->BarInner.setSize(sf::Vector2f(width, height));
	this->BarInner.setFillColor(inner_color);
	this->BarInner.setPosition(this->BarBack.getPosition());

	if (font)
	{
		this->BarText.setFont(*font);
		this->BarText.setCharacterSize(gui::calcCharSize(vm, character_size));
		this->BarText.setPosition(this->BarInner.getPosition().x + gui::p2pX(0.53f, vm),
			this->BarInner.getPosition().y + gui::p2pY(0.5f, vm));
	}
}

gui::ProgressBar::~ProgressBar()
{

}

//Functions
void gui::ProgressBar::update(const int current_value, const int max_value)
{
	float percent = static_cast<float>(current_value) / static_cast<float>(max_value);

	this->BarInner.setSize(
		sf::Vector2f
		(
			static_cast<float>(std::floor(this->BarMaxWidth * percent)),
			this->BarInner.getSize().y
		)
	);

	this->BarString = std::to_string(current_value) + " / " + std::to_string(max_value);
	this->BarText.setString(this->BarString);
}

void gui::ProgressBar::render(sf::RenderTarget& target)
{
	target.draw(this->BarBack);
	target.draw(this->BarInner);
	target.draw(this->BarText);
}

//================================================================================================================
gui::Circleshape::Circleshape(float _x, float _y, float _radius, unsigned character_size, sf::VideoMode& vm, sf::Font* font)
{
	this->circlestate = CircleState::circle_nrml;
	float radius = gui::p2p(_radius, vm);
	float x = gui::p2pX(_x, vm);
	float y = gui::p2pY(_y, vm);

	this->shape.setPosition(x, y);
	this->shape.setRadius(radius);
	this->shape.setFillColor(sf::Color(50, 255, 50, 255));

	this->BarText.setFont(*font);
	this->BarText.setCharacterSize(gui::calcCharSize(vm, character_size));
	this->BarText.setPosition(this->shape.getPosition().x + gui::p2pX(0.17f, vm),
		this->shape.getPosition().y - gui::p2pY(1.1,vm));
	this->BarText.setString("+");
}

gui::Circleshape::~Circleshape()
{
}

bool gui::Circleshape::update(const sf::Vector2i& mousePosWindow)
{
	this->circlestate = CircleState::circle_nrml;
	//HOVER
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->circlestate = CircleState::circle_clicked;
		}
	}
	switch (this->circlestate)
	{
	case circle_nrml:
		this->shape.setFillColor(sf::Color(50, 255, 50, 200));
		this->BarText.setFillColor(sf::Color::White);
		break;
	case circle_clicked:
		this->shape.setFillColor(sf::Color(50, 255, 50, 255));
		this->BarText.setFillColor(sf::Color(255, 255, 0, 255));
		return true;
		break;
	default:
		this->shape.setFillColor(sf::Color::Green);
		this->BarText.setFillColor(sf::Color::Green);
		break;
	}
	return false;
}

void gui::Circleshape::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->BarText);
}

