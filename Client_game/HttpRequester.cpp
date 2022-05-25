#include "HttpRequester.h"

void HttpRequester::init(){

    static bool flag{ false };
    if (!flag) {

        curl_global_init(CURL_GLOBAL_DEFAULT);

        flag = true;

    }

}

void HttpRequester::clean(){

    static bool flag{ false };
    if (!flag) {

        curl_global_cleanup();

        flag = true;

    }
    
}

HttpRequester::HttpRequester()
{/*plug*/}

HttpRequester* HttpRequester::instance{};

HttpRequester& HttpRequester::getInstance() {

    static std::once_flag flag;

    if (!instance) {

        std::call_once(flag, []() { instance = new HttpRequester(); });

    }

    return *instance;

}

size_t HttpRequester::my_write(void* buffer, size_t size, size_t nmemb, void* param){

    std::string& text = *static_cast<std::string*>(param);
    size_t totalsize = size * nmemb;
    text.append(static_cast<char*>(buffer), totalsize);
    return totalsize;

}


CURLcode HttpRequester::getLastError(){

    return lastErrorCode_;

}

std::pair<std::string, int> HttpRequester::GETrequest(const std::string& host, const std::string& URI){

    std::string result;
    CURL* curl_ =  curl_easy_init();
    if (!curl_) {

        Logger::getInstance()->error("CURL init error");
        return { result, -1 };

    }

    std::string url{ host + URI };
    Logger::getInstance()->info("Make GET request to " + url);
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &HttpRequester::my_write);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1L);

    lastErrorCode_ = curl_easy_perform(curl_);
    long int responseCode;
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &responseCode);
    curl_easy_cleanup(curl_);
    if (CURLE_OK != lastErrorCode_) {

       std::string error{ "CURL error: " };
       std::ostringstream oss;
       oss << lastErrorCode_;
       error += oss.str();

       Logger::getInstance()->error(error);

       return {result, lastErrorCode_};

    }
    else {

        std::string success{ "Request to " + url + " successfull, code: " };
        std::ostringstream oss;
        oss << responseCode;
        Logger::getInstance()->info(success + oss.str());

        return { result, responseCode };

    }
    
}

