#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "SettingsProfileLoader.h"

int main(){

    SettingsProfile settingsProfile{ SettingsProfileLoader::load() };

    sf::RenderWindow window(sf::VideoMode(200, 200), "Client");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);


    sf::UdpSocket socket;

    // bind the socket to a port
    if (socket.bind(settingsProfile.getPort()) != sf::Socket::Done)
    {
        // error...
        shape.setFillColor(sf::Color::Red);
    }

    char data[100];
   
    sf::Clock clock;

    sf::Thread thread([&]() {
        while (true)
        {

            time_t clientTime;

            time(&clientTime);

            sprintf_s<100>(data, "%lld", clientTime);

            if (socket.send(data, 100, settingsProfile.getIp(), settingsProfile.getPort()) != sf::Socket::Done)
            {
                shape.setFillColor(sf::Color::Red);
            }
            else {

                shape.setFillColor(sf::Color::Green);

            }
        }
        

        });

    // run it
    thread.launch();
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
    thread.terminate();

    return 0;
}