#pragma once
#include <SFML/Network.hpp>

class Settings{
	
public:

	Settings();
	Settings(size_t port, const sf::IpAddress & ip);

	void setPort(size_t port);
	void setIp(const sf::IpAddress& ip);
	void setLogLevel(std::string logLevel);

	size_t getPort();
	sf::IpAddress getIp();
	std::string getLogLevel();

private:

	size_t port_;
	sf::IpAddress ip_;
	std::string logLevel_;

};

