#include "nlohmann/json.hpp"
#include "HttpRequester.h"
#include "RequestInformer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "SettingsProfileLoader.h"
#include "Logger.h"
#include <iostream>
#include "ConnectionLoader.h"
#include "ConnectionScreen.h"
#include "ScreenWithLoader.h"
#include "DataLoadScreen.h"
#include "DataLoader.h"

class Entity {
public:

    enum Type{ OBJECT, SWORD, SPEAR, BOW, MAGIC };


private:

    std::string imageName_;
    int type_;

};

#include "Button.h"
#include "InputWindow.h"

void loginScreen(sf::RenderWindow & window) {

    sf::Font font{};
    font.loadFromFile("fonts/consola.ttf");
    //106 116 58
    //75 82 41
    sf::Vector2f winSize(400, 80);
    InputWindow inputWindow{ font };
    inputWindow.setTextColor(sf::Color::White);
    inputWindow.setTextOutlineThickness(1.f);
    inputWindow.setTextOutlineColor(sf::Color::Black);
    inputWindow.setFrameColor(sf::Color(75, 82, 41));
    inputWindow.setFrameSize(winSize);
    inputWindow.setFrameOutlineThickness(4.f);
    inputWindow.setFrameOutlineColor(sf::Color::Black);
    inputWindow.setCharacterSize(34);
    inputWindow.setPosition(sf::Vector2f(window.getSize()) / 2.f-winSize/2.f);

    while (window.isOpen())
    {

        sf::Event event;
        sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition = window.mapPixelToCoords(pixelPosition);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (inputWindow.isFocusedCheck(event, mousePosition)) {

                inputWindow.updateByEvent(event);

                if (inputWindow.isEnterPressed()) {

                    inputWindow.lostFocus();

                }

            }
        }

        inputWindow.update();

        window.clear(sf::Color(106, 116, 58));

        window.draw(inputWindow);
        window.display();

    }

}


int main(){

    SettingsProfile settingsProfile{ SettingsProfileLoader::load() };

    Logger::getInstance()->setLevel(settingsProfile.getLogLevel());
    Logger::getInstance()->info("Settings were load successfully");

    HttpRequester::getInstance().init();
    RequestInformer::getInstance().init();

    RequestInformer::getInstance().setHost(settingsProfile.getIp(), settingsProfile.getPort());
   
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);
    sf::RenderWindow window(sf::VideoMode(800, 800), "Client");
    //auto [result, code] {HttpRequester::getInstance().GETrequest(RequestInformer::getInstance().getHost(), "/auth?ip=" + RequestInformer::getInstance().getClientIp())};

    int registered{ 0 };
    {

        Loader * loader = new ConnectionLoader;
        Screen * screen = new ConnectionScreen;

        ScreenWithLoader loginCheck(screen, loader);
        loginCheck.run(window);

        registered = reinterpret_cast<ConnectionLoader*>(loader)->getRegistered();
        if (registered == 2) {

            return 0;

        }

        delete loader;
        delete screen;

    }
    int loaded{ 0 };
    {

        Loader* loader = new DataLoader;
        Screen* screen = new DataLoadScreen;

        ScreenWithLoader dataLoad(screen, loader);
        dataLoad.run(window);

        loaded = reinterpret_cast<DataLoader*>(loader)->getLoaded();
        if (loaded == 0) {

            return 0;

        }

        delete loader;
        delete screen;

    }

    
    loginScreen(window);

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /*sprintf_s<100>(data, "%f", clock.getElapsedTime().asSeconds());
        if (socket.send(data, 100, recipient, port) != sf::Socket::Done)
        {
            shape.setFillColor(sf::Color::Red);
        }
        else {

            shape.setFillColor(sf::Color::Green);

        }*/

        window.clear();
        window.draw(shape);
        window.display();
    }

    HttpRequester::getInstance().clean();

    return 0;
}
