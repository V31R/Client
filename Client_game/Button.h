#pragma once
#include <SFML/Graphics.hpp>
#include "Functor.h"

class NonTextedButton : public sf::Drawable, public sf::Transformable {
public:
	NonTextedButton();
	NonTextedButton(float x, float y, float width, float height,
		float thickness, const sf::Color & outLineColor,
		const sf::Color & idleColor, const sf::Color & hoverColor, const sf::Color & activeColor);
	NonTextedButton( const sf::Color & idleColor, const sf::Color & hoverColor, const sf::Color & activeColor);

	enum States { IDLE, HOVER, ACTIVE };

	void setSize(const sf::Vector2f &);
	sf::Vector2f getSize();
	bool isPressed();
	bool update(const sf::Vector2f & mousePosition);
	void paintButton();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setOutlineThickness(float);
	float getOutlineThickness();
	void setOutlineColor(const sf::Color &, const sf::Color & hoverColor = sf::Color::Black);
	sf::RectangleShape getShape();

	void setFunction(Functor &func);
	void callFunction();
	
private:
	unsigned short buttonState;

	sf::RectangleShape shape;

	sf::Color outlineColor_;
	sf::Color outlineHoverColor_;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	Functor *function;

	sf::Clock clock;
};

class Button: public NonTextedButton {
public:
	Button() {};
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, float thickness, sf::Color outLineColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) :NonTextedButton(x, y, width, height,
			thickness, outLineColor, idleColor, hoverColor, activeColor), font_(font)
	{
		font_ = font;
		text_.setFont(*this->font_);
		text_.setString(text);
		text_.setFillColor(sf::Color::White);
		text_.setOutlineColor(sf::Color::Black);
		text_.setOutlineThickness(1);
		text_.setCharacterSize(17);
		text_.setPosition(
			(x + getShape().getGlobalBounds().width / 2) - (text_.getGlobalBounds().width / 2),
			(y + getShape().getGlobalBounds().height / 2) - (text_.getGlobalBounds().height)
		);
	};

	~Button();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setText(std::string str);
	void setTextSize(unsigned int size);
	
private:
	sf::Font* font_;
	sf::Text text_;
	
};