#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "SettingsProfileLoader.h"
#include "Logger.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)
#define CURL_STATICLIB
#include <curl/curl.h>
#include"HttpRequester.h"


sf::String getMyIP() {
    struct hostent* hostName = gethostbyname("");
    SOCKADDR_IN serverAddress;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.S_un.S_addr = *(DWORD*)hostName->h_addr_list[0];

    return sf::String(inet_ntoa(serverAddress.sin_addr));
}


int main(){
    //test_curl();
    HttpRequester::getInstance().init();

    WSADATA WSAData;
    if (WSAStartup(0x0202, &WSAData)) {
        return 1;
    }

    SettingsProfile settingsProfile{ SettingsProfileLoader::load() };

    Logger::getInstance()->setLevel(settingsProfile.getLogLevel());
    Logger::getInstance()->info("Settings were load successfully");

   
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);

    sf::String clientIp{ getMyIP() };
    std::string baseHost("http://" + settingsProfile.getIp().toString() + ":");
    {
        std::ostringstream oss;
        oss << settingsProfile.getPort();
        baseHost += oss.str();
    }

    std::string res = HttpRequester::getInstance().GETrequest(baseHost, "/auth?ip=" + clientIp);

   
  //  (sf::String("This client ip = ") + clientIp).toAnsiString();
   // Logger::getInstance()->info((sf::String("This client ip = ") + clientIp).toAnsiString());

    //sf::Http http;
    //std::string baseHost("http://" + settingsProfile.getIp().toString() + ":");
    //{
    //    std::ostringstream oss;
    //    oss << settingsProfile.getPort();
    //    baseHost += oss.str();
    //}
    //baseHost += "/";
    //http.setHost(baseHost);
    ////http.setHost("http://localhost:8080");
    ////http.setHost("www.sfml-dev.org/");
    ////http.setHost("ru.wikipedia.org/");
    ////http.setHost("www.whatismyip.org");
    //sf::Http::Request request;
    //request.setMethod(sf::Http::Request::Method::Get);
   
    ////request.setUri("features.php");
    ////request.setUri("/auth?ip=" + clientIp);
    ////request.setHttpVersion(1, 1); // HTTP 1.1
    //request.setField("User-Agent", "libsfml-network/1.x");
    //request.setField("Connection", "keep-alive");
    ////request.setField("Connection", "Closed");
    //request.setField("Accept", "*/*");
    //request.setField("Accept-Encoding", "gzip, deflate, br");

    //// fill the request...
    //sf::Http::Response response = http.sendRequest(request);
    //
    //sf::String responseStatus;
    //{
    //    std::ostringstream oss;
    //    oss << response.getStatus();
    //    responseStatus += oss.str();
    //}
    //Logger::getInstance()->info("Request for login with status code = " + responseStatus+" with body\n"+response.getBody());
    //// run it
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
