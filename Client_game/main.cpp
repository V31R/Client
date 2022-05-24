#include <#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "SettingsProfileLoader.h"
#include "Logger.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)

sf::String getMyIP() {
    struct hostent* hostName = gethostbyname("");
    SOCKADDR_IN serverAddress;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.S_un.S_addr = *(DWORD*)hostName->h_addr_list[0];

    return sf::String(inet_ntoa(serverAddress.sin_addr));
}


int main(){
    WSADATA WSAData;
    if (WSAStartup(0x0202, &WSAData)) {
        return 1;
    }

    SettingsProfile settingsProfile{ SettingsProfileLoader::load() };

    Logger::getInstance()->setLevel(settingsProfile.getLogLevel());
    Logger::getInstance()->info("Settings were load successfully");

    sf::RenderWindow window(sf::VideoMode(200, 200), "Client");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);

    std::cout << getMyIP().toAnsiString();

    // run it
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

    return 0;
}
