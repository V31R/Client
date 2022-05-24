#pragma once
#include <SFML/Graphics.hpp>

class InputWindow : public sf::Drawable, public sf::Transformable {
public:

	InputWindow(sf::Font& font);

	bool isFocusedCheck(sf::Event & event, const sf::Vector2f & mousePosition);
	bool isFocused();
	void lostFocus();

	void updateByEvent(sf::Event& event);
	void update();
	void setFrameSize(const sf::Vector2f& size);
	void setFrameColor(const sf::Color& color);
	void setFrameOutlineColor(const sf::Color& color);
	void setFrameOutlineThickness(float thickness);

	void setCharacterSize(size_t size);
	void setTextColor(const sf::Color& color);
	void setTextOutlineColor(const sf::Color& color);
	void setTextOutlineThickness(float thickness);

	sf::String getString()const;

	bool isEnterPressed()const;


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setTextParameters();
	void backspace();
	void setPositions();


	size_t state_;
	bool isFocused_;
	bool isEnterPressed_;

	sf::Font& font_;
	sf::Text text_;

	sf::RectangleShape frame_;

	sf::String string_;
	sf::String currentString_;
	size_t startStringIndex_;
	size_t numberCharacter_;
	float height_;
	float offset_;


	sf::RectangleShape cursor_;
	size_t cursorTextPosition_;
	float cursorPosition_;
	float cursorWidth_;

	sf::Clock clock_;

};

