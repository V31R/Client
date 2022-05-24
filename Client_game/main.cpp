#include "nlohmann/json.hpp"
#include "HttpRequester.h"
#include "RequestInformer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "SettingsProfileLoader.h"
#include "Logger.h"
#include <iostream>

class Entity {
public:

    enum Type{ OBJECT, SWORD, SPEAR, BOW, MAGIC };



private:

    std::string imageName_;
    int type_;

}; 

int main(){

    HttpRequester::getInstance().init();
    RequestInformer::getInstance().init();
    SettingsProfile settingsProfile{ SettingsProfileLoader::load() };


    Logger::getInstance()->setLevel(settingsProfile.getLogLevel());
    Logger::getInstance()->info("Settings were load successfully");

    RequestInformer::getInstance().setHost(settingsProfile.getIp(), settingsProfile.getPort());
   
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);

    std::string res = HttpRequester::getInstance().GETrequest(RequestInformer::getInstance().getHost(), "/auth?ip=" + RequestInformer::getInstance().getClientIp());

    sf::RenderWindow window(sf::VideoMode(200, 200), "Client");
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
