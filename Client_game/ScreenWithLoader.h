#pragma once
#include "Screen.h"
#include "Loader.h"
#include <thread>

class ScreenWithLoader{
public:

	ScreenWithLoader(Screen * screen, Loader * loader);
	~ScreenWithLoader();
	void run(sf::RenderWindow & window);

private:

	int* state;
	Screen * screen_;
	Loader * loader_;

};

