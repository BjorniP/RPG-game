#pragma once

//Buttons that determine MianState/GameState
enum button_state { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED };

namespace gui
{
	const float p2pX(const float perc, sf::VideoMode& vm);
	const float p2pY(const float perc, sf::VideoMode& vm);
	const float p2p(const float perc, sf::VideoMode& vm);
	const unsigned calcCharSize(sf::VideoMode& vm, const unsigned modifier = 60);
    class Button
	{
	private:
		//variables that we use to design the button (Size/Color/Shape)
		short unsigned buttonState;
		short unsigned id;

		sf::Font* font;
		sf::Text text;
		sf::RectangleShape shape;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;
	public:
		//Cons/Destructors
		Button(
			float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color,
			sf::Color outline_idle_Color = sf::Color::Transparent, sf::Color outline_hover_Color = sf::Color::Transparent,
			sf::Color outline_active_Color = sf::Color::Transparent
			, short unsigned id = 0
		);
		virtual ~Button();

		//Accessories
		//const bool& isPressed1() const;
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Public functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};

	class DropDownList {
	private:

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showlist;
		float keytimer;
		float keytimerMax;

	public:
		DropDownList(float x, float y, float width, float height, int CharSize,
			sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
		virtual ~DropDownList();

		//Accessories
		const bool getKeytimer();
	    const short unsigned& getActiveElementID()const;

		//Public functions
		void updateKeytimer(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		//Timer
		float keytimer;
		const float keytimerMax;

		bool active;
		bool hidden;
		float gridSize;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::IntRect textureRect;
		sf::Vector2u mousePosGrid;

		Button* hide_btn;

	public:
		TextureSelector(float x, float y, float width, float height, float gridsize,
			const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		//Accessories
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeytimer();

		//Functions
		void updateKeytimer(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	
	class ProgressBar
	{
	private:
		std::string BarString;
		sf::Text BarText;
		sf::RectangleShape BarInner;
		sf::RectangleShape BarBack;
		float BarMaxWidth;
	public:
		ProgressBar(float x, float y, float width, float height,
			sf::Color inner_color,unsigned character_size, sf::VideoMode& vm, sf::Font* font = NULL);
		virtual ~ProgressBar();

		void update(const int current_value, const int max_value);
		void render(sf::RenderTarget& target);
	};

	enum CircleState { circle_nrml = 0, circle_clicked };
	class Circleshape
	{
	 private:
		 short unsigned circlestate;
		 sf::CircleShape shape;
		 sf::Text BarText;
	public:
		Circleshape(float _x, float _y, float _radius,unsigned character_size, sf::VideoMode& vm, sf::Font* font);
		virtual ~Circleshape();
		bool update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};
}

