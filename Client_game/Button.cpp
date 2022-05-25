#include "Button.h"

NonTextedButton::NonTextedButton()
	{}

NonTextedButton::NonTextedButton(float x, float y, float width, float height,
	float thickness, const sf::Color & outLineColor,
	const sf::Color & idleColor, const sf::Color & hoverColor, const sf::Color & activeColor):
	NonTextedButton{idleColor, hoverColor,activeColor}
{
	
	setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));

	//Рамка 
	shape.setOutlineThickness(thickness);
	shape.setOutlineColor(outLineColor);


	shape.setFillColor(idleColor);
}

NonTextedButton::NonTextedButton(const sf::Color & idleColor, const sf::Color & hoverColor, const sf::Color & activeColor):
	idleColor{ idleColor },
	hoverColor{ hoverColor },
	activeColor{ activeColor }
{
	shape.setFillColor(this->idleColor);
}


void NonTextedButton::setSize(const sf::Vector2f & size){

	shape.setSize(size);

}

sf::Vector2f NonTextedButton::getSize(){

	return shape.getSize();

}

bool NonTextedButton::isPressed(){ 

	if ( clock.getElapsedTime().asMilliseconds()  > 125) {

		clock.restart();
		if (buttonState == ACTIVE) {

			function->call();

		}
		
		return true;

	}
	
	return false;

}

bool NonTextedButton::update(const sf::Vector2f & mousePosition) {

	buttonState = IDLE;
	sf::Vector2f mousePos{ mousePosition - getPosition() };
	if (this->shape.getGlobalBounds().contains(mousePos)) {

		this->buttonState = HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			this->buttonState = ACTIVE;

		}

	}
	paintButton();
	return isPressed();

}

void NonTextedButton::paintButton(){

	switch (this->buttonState){

	case IDLE:
		this->shape.setFillColor(idleColor);
		shape.setOutlineColor(outlineColor_);
		break;
	case HOVER:
		this->shape.setFillColor(hoverColor);
		shape.setOutlineColor(outlineHoverColor_);
		break;
	case ACTIVE:
		this->shape.setFillColor(activeColor);
		shape.setOutlineColor(outlineHoverColor_);
		break;

	}

}



void NonTextedButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	states.transform *= getTransform();

	target.draw(shape, states);

}

void NonTextedButton::setOutlineThickness(float thickness){

	shape.setOutlineThickness(thickness);

}

float NonTextedButton::getOutlineThickness(){

	return shape.getOutlineThickness();

}

void NonTextedButton::setOutlineColor(const sf::Color & color, const sf::Color & hoverColor){

	outlineColor_ = color;
	outlineHoverColor_ = hoverColor;

}


sf::RectangleShape NonTextedButton::getShape(){

	return shape;

}

void NonTextedButton::setFunction(Functor& func){

	function = &func;

}

void NonTextedButton::callFunction(){

		function->call();

}

Button::~Button(){

}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	NonTextedButton::draw(target, states);
	//states.transform *= getTransform();

	target.draw(text_, states);
}

void Button::setText(std::string str){

	this->text_.setString(str);

}

void Button::setTextSize(unsigned int size){

	text_.setCharacterSize(size);

	sf::Vector2f s(getShape().getGlobalBounds().width, getShape().getGlobalBounds().height);
	sf::Vector2f ts(text_.getGlobalBounds().width, text_.getGlobalBounds().height);
	sf::Vector2f offset{ (s - ts)/2.f };

	text_.setPosition(
		this->getPosition().x + offset.x,
		this->getPosition().y + offset.y/2
	);


}


