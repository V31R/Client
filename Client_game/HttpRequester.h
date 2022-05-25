#pragma once

#include "Logger.h"
#include <sstream>
#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <mutex>
#include <utility>

class HttpRequester{
public:

    static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param);
    static HttpRequester& getInstance();

    void init();
    void clean();

    CURLcode getLastError();
    std::pair<std::string, int> GETrequest(const std::string& host, const std::string& URI);

private:

    HttpRequester();

    CURLcode lastErrorCode_;
    static HttpRequester* instance;

};


