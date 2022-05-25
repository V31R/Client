#include "ScreenWithLoader.h"

ScreenWithLoader::ScreenWithLoader(Screen * screen, Loader * loader):
	screen_{screen},
	loader_{loader}
{

	state = new int(0);

}

ScreenWithLoader::~ScreenWithLoader(){

	delete state;

}

void ScreenWithLoader::run(sf::RenderWindow & window){

	std::thread backgroundLoad([&]() {loader_->load(state); });
	screen_->show(window, state);
	backgroundLoad.join();

}
