#pragma once
#include <SFML/Network.hpp>
#include "Logger.h"
class Settings{
	
public:

	Settings();
	Settings(size_t port, const sf::IpAddress & ip);
	Settings(size_t port, const sf::IpAddress& ip, Logger::LogLevel logLevel);

	void setPort(size_t port);
	void setIp(const sf::IpAddress& ip);
	void setLogLevel(Logger::LogLevel logLevel);

	size_t getPort();
	sf::IpAddress getIp();
	Logger::LogLevel getLogLevel();

private:

	size_t port_;
	sf::IpAddress ip_;
	Logger::LogLevel logLevel_;

};

