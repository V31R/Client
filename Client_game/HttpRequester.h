#pragma once
#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "SettingsProfileLoader.h"
#include "Logger.h"
#include <iostream>

#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <mutex>

class HttpRequester{
public:

    static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param);
    static HttpRequester& getInstance();

    void init();
    void clean();

    CURLcode getLastError();
    std::string GETrequest(const std::string& host, const std::string& URI);

private:

    HttpRequester();

    CURLcode lastErrorCode_;
    static HttpRequester* instance;

};

