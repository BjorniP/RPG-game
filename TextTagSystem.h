#pragma once
enum TAGTYPES { DEFAULT_TAG = 0, NEGATIVE_TAG, POSITIVE_TAG, EXPERIENCE_TAG, ENVIRONMENT_TAG };
class TextTagSystem
{
private:
	class TextTag
	{
	private:
		sf::Text text;
		float dirX;
		float dirY;
		float speed;
		float lifetime;
		float acceleration;
		sf::Vector2f velocity;
		int fadeValue;
		bool reverse;
	public:
		TextTag(sf::Font& font,std::string text,
			float pos_x,float pos_y,float dir_x,float dir_y,
			sf::Color color,unsigned char_size, float speed, float lifetime, bool reverse, float acceleration, int fade_value)
		{
			this->text.setFont(font);
			this->text.setPosition(pos_x, pos_y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->text.setString(text);

			this->dirX = dir_x;
			this->dirY = dir_y;
			this->speed = speed;
			this->lifetime = lifetime;
			this->acceleration = acceleration;
			this->fadeValue = fade_value;
			this->reverse = reverse;
			if (this->reverse)
			{
				this->velocity.x = this->dirX * this->speed;
				this->velocity.y = this->dirY * this->speed;
			}
		}
		TextTag(TextTag* tag,
			float pos_x, float pos_y, std::string str)
		{
			this->text = tag->text;
			this->text.setString(str);
			this->text.setPosition(pos_x, pos_y);

			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->speed = tag->speed;
			this->lifetime = tag->lifetime;
			this->acceleration = tag->acceleration;
			this->fadeValue = tag->fadeValue;
			this->reverse = tag->reverse;
			this->velocity = tag->velocity;
		}

		virtual ~TextTag()
		{

		}

		inline const bool canBeRemoved() const { return this->lifetime <= 0.f; }

		void update(const float& dt)
		{
			if (this->lifetime > 0.f)
			{
				this->lifetime -= 100.f * dt;

				if (this->acceleration > 0.f)
				{
					if (this->reverse)
					{
						this->velocity.x -= this->dirX * this->acceleration * dt;
						this->velocity.y -= this->dirY * this->acceleration * dt;

						if (abs(this->velocity.x) < 0.f)
							this->velocity.x = 0.f;
						if (abs(this->velocity.y) < 0.f)
							this->velocity.y = 0.f;

						this->text.move(this->velocity * dt);
					}
					else
					{
						this->velocity.x += this->dirX * this->acceleration * dt;
						this->velocity.y += this->dirY * this->acceleration * dt;

						if (abs(this->velocity.x) > this->speed)
							this->velocity.x = this->dirX * this->speed;
						if (abs(this->velocity.y) > this->speed)
							this->velocity.y = this->dirY * this->speed;

						this->text.move(this->velocity * dt);
					}
					
				}
				else
				{
					this->text.move(this->dirX * speed * dt, this->dirY * speed * dt);
				}

				if (this->fadeValue > 0 && this->text.getFillColor().a >= this->fadeValue)
				{
					this->text.setFillColor
					(
						sf::Color(
							this->text.getFillColor().r,
							this->text.getFillColor().g,
							this->text.getFillColor().b,
							this->text.getFillColor().a - this->fadeValue
						)
					);
				}
			}
		}

		void render(sf::RenderTarget& target)
		{
			target.draw(this->text);
		}
	};

	sf::Font font;
	std::map<unsigned int, TextTag*>tagTemplates;
	std::vector<TextTag*> tags;
	void initVariables();
	void initFont(std::string font_file);
	void initTagTemplates();
public:
	TextTagSystem(std::string font_file);
	virtual ~TextTagSystem();

	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const std::string str, const std::string prefix = "", const std::string postfix = "");
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, const std::string prefix = "", const std::string postfix = "");
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, const std::string prefix = "", const std::string postfix = "");
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

