#pragma once
#include <SFML/Graphics.hpp>
class Screen{
public:

	virtual void show(sf::RenderWindow& window, int * state) = 0;

};

