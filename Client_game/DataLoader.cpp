#include "DataLoader.h"
using json = nlohmann::json;
DataLoader::DataLoader() :

    loaded_{ 0 }

{}
void DataLoader::load(int* state){

    int number{ 0 };
    int code_;
    std::string result_;
    loaded_ = 1;
    do {

        auto [result, code] {HttpRequester::getInstance().GETrequest(RequestInformer::getInstance().getHost(), "/images")};
        code_ = code;
        result_ = result;
        if (code != CURLE_OK) {

            using namespace std::chrono_literals;
            number++;
            std::this_thread::sleep_for(1000ms);

        }

    } while (number < 5 && code_ != 200);
   
    if (number == 5) {

        loaded_ = 0;

    }
    else {

        json array = json::parse(result_);

        std::vector<std::string> list;
        for (auto& elem : array) {

            list.push_back(elem);

        }
        for (auto imageName : list) {

            std::ifstream image;
            image.open("images/" + imageName);
            if (!image.is_open()) {

                int number{ 0 };
                int code_;
                std::string result_;
                do {

                    auto [result, code] {HttpRequester::getInstance().GETrequest(RequestInformer::getInstance().getHost(), "/images/load?name=" + imageName)};
                    code_ = code;
                    result_ = result;
                    if (code != CURLE_OK) {

                        using namespace std::chrono_literals;
                        number++;
                        std::this_thread::sleep_for(1000ms);

                    }

                } while (number < 5 && code_ != 200);

                if (number == 5) {

                    loaded_ = 0;

                }
                else {

                    std::ofstream image;
                    image.open("images/" + imageName);
                    image << result_;
                    image.close();

                }

            }
            else {

                image.close();

            }
        }
    }

    *state = 1;

}

int DataLoader::getLoaded() const {

    return loaded_;

}
