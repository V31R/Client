#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "SettingsProfileLoader.h"

#define IP "172.22.15.218"
#ifndef $(VLAD_PC)
#undef IP
#define IP "172.22.111.11"
#endif

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Client");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);

    SettingsProfile settings{ 9993, IP };

    auto test{ SettingsProfileLoader::load() };

    sf::UdpSocket socket;

    // bind the socket to a port
    if (socket.bind(settings.getPort()) != sf::Socket::Done)
    {
        // error...
        shape.setFillColor(sf::Color::Red);
    }

    char data[100];

    printf(IP);
   
    sf::Clock clock;

    sf::Thread thread([&]() {
        while (true)
        {

            time_t clientTime;

            time(&clientTime);

            sprintf_s<100>(data, "%lld", clientTime);

            if (socket.send(data, 100, settings.getIp(), settings.getPort()) != sf::Socket::Done)
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