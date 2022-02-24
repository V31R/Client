#include "SettingsProfile.h"

SettingsProfile::SettingsProfile() : 

    Settings{}

{}

SettingsProfile::SettingsProfile(size_t port, const sf::IpAddress& ip):

    Settings{port, ip}

{}

SettingsProfile::SettingsProfile(size_t port, const sf::IpAddress& ip, const std::string& name) :

    Settings{ port, ip },
    name_{ name }

{}

void SettingsProfile::setName(const std::string& name){

    name_ = name;

}

std::string SettingsProfile::getName(){

    return name_;

}
