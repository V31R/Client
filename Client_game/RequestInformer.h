#pragma once

#include "Logger.h"

#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <mutex>

class RequestInformer{
public:

    static RequestInformer& getInstance();

    void init();

    void setHost(const sf::IpAddress& ip, size_t port);

    sf::String getClientIp();
    std::string getHost();


private:

    sf::String getMyIP();

    RequestInformer();

    sf::String clientIP_;
    std::string host_;
    static RequestInformer* instance;

};

