#pragma once
#include <SFML/Network.hpp>
#include "Logger.h"
class Settings{
	
public:

	Settings();
	Settings(size_t port, const sf::IpAddress & ip);
	Settings(size_t port, const sf::IpAddress& ip, Logger::logLevel logLevel);

	void setPort(size_t port);
	void setIp(const sf::IpAddress& ip);
	void setLogLevel(Logger::logLevel logLevel);

	size_t getPort();
	sf::IpAddress getIp();
	Logger::logLevel getLogLevel();

private:

	size_t port_;
	sf::IpAddress ip_;
	Logger::logLevel logLevel_;

};

