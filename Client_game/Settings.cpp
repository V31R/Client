#include "Settings.h"

Settings::Settings()
	{/* plug */}

Settings::Settings(size_t port, const sf::IpAddress& ip):

	port_{port},
	ip_{ip}

{}

void Settings::setPort(size_t port){

	port_ = port;

}

void Settings::setIp(const sf::IpAddress& ip){

	ip_ = ip;

}

size_t Settings::getPort(){

	return port_;

}

sf::IpAddress Settings::getIp(){

	return ip_;

}
