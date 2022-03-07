#pragma once
#include "Settings.h"
#include <string>

class SettingsProfile : public Settings{

public:

	SettingsProfile();
	SettingsProfile(size_t port, const sf::IpAddress & ip);
	SettingsProfile(size_t port, const sf::IpAddress & ip, const std::string & name);
	SettingsProfile(size_t port, const sf::IpAddress& ip, Logger::LogLevel logLevel_);

	void setName(const std::string & name);
	std::string getName();
	
private:

	std::string name_;

};

