#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "SettingsProfileLoader.h"


int main(){

    SettingsProfile settingsProfile{ SettingsProfileLoader::load() };

    Logger::getInstance()->setLevel(settingsProfile.getLogLevel());
    Logger::getInstance()->info("Settings were load successfully");

    sf::RenderWindow window(sf::VideoMode(200, 200), "Client");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);


    sf::UdpSocket socket;

    // bind the socket to a port
    /*if (socket.bind(settingsProfile.getPort()) != sf::Socket::Done)
    {
        // error...
        shape.setFillColor(sf::Color::Red);

    }*/

    sf::TcpSocket socketTCP;
    std::cout << socketTCP.connect("127.0.0.1", 5000);

    std::string message = "Hi, I am a client";
    socketTCP.send(message.c_str(), message.size() + 1);

    char buffer[1024];
    std::size_t received = 0;
    socketTCP.receive(buffer, sizeof(buffer), received);
    std::cout << "The server said: " << buffer << std::endl;

    char data[272];
   
    sf::Clock clock;

    sf::Thread thread([&]() {
        while (true)
        {

            time_t clientTime;
            
            time(&clientTime);
            int64_t dataTime = clientTime;
            memset(data, 0, 8);
            memcpy(data + 8,&dataTime,sizeof(dataTime));
            //sprintf_s<264>(data+8, "", clientTime);

            if (socketTCP.send(data, 272) != sf::Socket::Done)
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