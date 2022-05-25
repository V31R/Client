#include "ConnectionLoader.h"

void ConnectionLoader::load(int* state){

    int number{ 0 };
    int code_;
    std::string result_;
    do {

        auto [result, code] {HttpRequester::getInstance().GETrequest(RequestInformer::getInstance().getHost(), "/auth?ip=" + RequestInformer::getInstance().getClientIp())};
        code_ = code;
        result_ = result;
        if (code != CURLE_OK) {

            using namespace std::chrono_literals;
            number++;
            std::this_thread::sleep_for(1000ms);

        }

    } while (number < 5 && code_ != 200);

    if (number == 5) {

        registered_ = 2;

    }
    else {

        std::istringstream iss{result_};
        iss >> registered_;

    }

    *state = 1;

}

int ConnectionLoader::getRegistered() const {

    return registered_;

}
