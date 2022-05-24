#include "RequestInformer.h"


RequestInformer* RequestInformer::instance{};


RequestInformer& RequestInformer::getInstance(){

    static std::once_flag flag;

    if (!instance) {

        std::call_once(flag, []() { instance = new RequestInformer(); });

    }

    return *instance;

}

void RequestInformer::init(){

    static bool flag{ false };
    if (!flag) {

        WSADATA WSAData;
        int res{ WSAStartup(0x0202, &WSAData) };
        if (res) {

            std::string error{ "WSAStartup error: " };
            std::ostringstream oss;
            oss << res;
            error += oss.str();

            Logger::getInstance()->error(error);
            return;

        }

        flag = true;

        clientIP_ = getMyIP();

    }

}

void RequestInformer::setHost(const sf::IpAddress& ip, size_t port){

    host_ = "http://" + ip.toString()+":";
    {
        std::ostringstream oss;
        oss << port;
        host_ += oss.str();
    }

}

sf::String RequestInformer::getClientIp(){

    return clientIP_;

}

std::string RequestInformer::getHost(){

    return host_;

}

sf::String RequestInformer::getMyIP(){

    struct hostent* hostName = gethostbyname("");
    SOCKADDR_IN serverAddress;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.S_un.S_addr = *(DWORD*)hostName->h_addr_list[0];

    return sf::String(inet_ntoa(serverAddress.sin_addr));
}

RequestInformer::RequestInformer()
{/*plug*/}
