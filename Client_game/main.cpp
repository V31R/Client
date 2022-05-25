#include "nlohmann/json.hpp"
#include "HttpRequester.h"
#include "RequestInformer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "SettingsProfileLoader.h"
#include "Logger.h"
#include <iostream>
#include "ConnectionLoader.h"
#include "ConnectionScreen.h"
#include "ScreenWithLoader.h"
#include "DataLoadScreen.h"
#include "DataLoader.h"

class Entity {
public:

    enum Type{ OBJECT, SWORD, SPEAR, BOW, MAGIC };


private:

    std::string imageName_;
    int type_;

};

#include "Button.h"
#include "InputWindow.h"
#include "Functor.h"

struct LoginData {
    sf::String name;
    int login;
};

class LoginFunction : public Functor {
public:
    LoginFunction(void* data) : Functor(data) {};
    void call() {
        LoginData* data = static_cast<LoginData*>(getData());
        data->login = 1;
        //std::cout << "test " << data->name.toAnsiString() << "\n";

        int number{ 0 };
        int code_;

        std::string result_;
        do {

            auto [result, code] {HttpRequester::getInstance().POSTrequest(RequestInformer::getInstance().getHost(), "/auth?ip=" +
                RequestInformer::getInstance().getClientIp() 
                + "&name=" + data->name.toAnsiString())};
            code_ = code;
            result_ = result;
            if (code != CURLE_OK) {

                using namespace std::chrono_literals;
                number++;
                std::this_thread::sleep_for(500ms);

            }

        } while (number < 5 && code_ != 200);

        if (number == 5) {

            data->login = 0;

        }


    }
};


void loginScreen(sf::RenderWindow & window) {

    sf::Font font{};
    font.loadFromFile("fonts/consola.ttf");
    //106 116 58
    //75 82 41
    sf::Vector2f winSize(400, 80);
    InputWindow inputWindow{ font };
    inputWindow.setTextColor(sf::Color::White);
    inputWindow.setTextOutlineThickness(1.f);
    inputWindow.setTextOutlineColor(sf::Color::Black);
    inputWindow.setFrameColor(sf::Color(75, 82, 41));
    inputWindow.setFrameSize(winSize);
    inputWindow.setFrameOutlineThickness(4.f);
    inputWindow.setFrameOutlineColor(sf::Color::Black);
    inputWindow.setCharacterSize(34);
    inputWindow.setPosition(sf::Vector2f(window.getSize()) / 2.f-winSize/2.f);

    sf::Vector2f btnSize(300, 80);

    LoginData loginData;
    loginData.login = 0;

    Button btn = Button(window.getSize().x / 2.f- btnSize.x/2, window.getSize().y / 4.f*3.f- btnSize.y/2, btnSize.x, btnSize.y, 
        &font, sf::String("LOGIN"), 4,
        sf::Color::Black, sf::Color(75, 82, 41), sf::Color(85, 92, 51), sf::Color(106, 116, 58));

    LoginFunction f = LoginFunction((void*)&loginData);
    btn.setTextSize(34);
    btn.setFunction(f);
    //btn.callFunction();

    while (window.isOpen() && !loginData.login)
    {

        sf::Event event;
        sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition = window.mapPixelToCoords(pixelPosition);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

           
            if (inputWindow.isFocusedCheck(event, mousePosition)) {

                inputWindow.updateByEvent(event);

                if (inputWindow.isEnterPressed()) {
                    loginData.name = inputWindow.getString();
                    btn.callFunction();
                    inputWindow.lostFocus();

                }

            }
        }

        inputWindow.update();
        loginData.name = inputWindow.getString();
        btn.update(mousePosition);

        window.clear(sf::Color(106, 116, 58));

        window.draw(inputWindow);
        window.draw(btn);
        window.display();

    }

}


struct PlayData {
    int queued;
};

class PlayFunction : public Functor {
public:
    PlayFunction(void* data) : Functor(data) {};
    void call() {
        PlayData* data = static_cast<PlayData*>(getData());
        if (data->queued == 0) {
            data->queued = 1;

            int number{ 0 };
            int code_;

            std::string result_;
            do {

                auto [result, code] {HttpRequester::getInstance().POSTrequest(RequestInformer::getInstance().getHost(), "/wait_queue?ip=" + RequestInformer::getInstance().getClientIp())};
                code_ = code;
                result_ = result;
                if (code != CURLE_OK) {

                    using namespace std::chrono_literals;
                    number++;
                    std::this_thread::sleep_for(500ms);

                }

            } while (number < 5 && code_ != 200);

            if (number == 5) {

                data->queued = 0;

            }
        }

    }
};

void playScreen(sf::RenderWindow& window) {

    sf::Font font{};
    font.loadFromFile("fonts/consola.ttf");
    //106 116 58
    //75 82 41
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setCharacterSize(40);
    
    sf::String textString("Finging match: ");

    sf::Vector2f btnSize(300, 80);

    PlayData playData;
    playData.queued = 0;

    Button btn = Button(window.getSize().x / 2.f - btnSize.x / 2, window.getSize().y / 4.f * 3.f - btnSize.y / 2, btnSize.x, btnSize.y,
        &font, sf::String("PLAY"), 4,
        sf::Color::Black, sf::Color(75, 82, 41), sf::Color(85, 92, 51), sf::Color(106, 116, 58));

    PlayFunction f = PlayFunction((void*)&playData);
    btn.setTextSize(34);
    btn.setFunction(f);
    //btn.callFunction();
    sf::Clock clock;
    int time{ 0 };
    while (window.isOpen())
    {   
        if (!playData.queued) {

            clock.restart();

        }

        if (clock.getElapsedTime().asMilliseconds() > 1000) {

            time++;
            clock.restart();

        }

        sf::Event event;
        sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition = window.mapPixelToCoords(pixelPosition);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            btn.update(mousePosition);

        }
       

        

        window.clear(sf::Color(106, 116, 58));

        if (playData.queued) {

             std::ostringstream iss;
             iss << time;
             iss << " second(s)";
             text.setString(textString + iss.str());
             text.setPosition(sf::Vector2f(window.getSize()) / 2.f - sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) / 2.f);

        }

        window.draw(text);
        window.draw(btn);
        window.display();

    }

}

int main(){

    SettingsProfile settingsProfile{ SettingsProfileLoader::load() };

    Logger::getInstance()->setLevel(settingsProfile.getLogLevel());
    Logger::getInstance()->info("Settings were load successfully");

    HttpRequester::getInstance().init();
    RequestInformer::getInstance().init();

    RequestInformer::getInstance().setHost(settingsProfile.getIp(), settingsProfile.getPort());
   
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Client");
    //auto [result, code] {HttpRequester::getInstance().GETrequest(RequestInformer::getInstance().getHost(), "/auth?ip=" + RequestInformer::getInstance().getClientIp())};

    int registered{ 0 };
    {

        Loader * loader = new ConnectionLoader;
        Screen * screen = new ConnectionScreen;

        ScreenWithLoader loginCheck(screen, loader);
        loginCheck.run(window);

        registered = reinterpret_cast<ConnectionLoader*>(loader)->getRegistered();
        if (registered == 2) {

            return 0;

        }

        delete loader;
        delete screen;

    }
    int loaded{ 0 };
    {

        Loader* loader = new DataLoader;
        Screen* screen = new DataLoadScreen;

        ScreenWithLoader dataLoad(screen, loader);
        dataLoad.run(window);

        loaded = reinterpret_cast<DataLoader*>(loader)->getLoaded();
        if (loaded == 0) {

            return 0;

        }

        delete loader;
        delete screen;

    }

    if (!registered) {

        loginScreen(window);

    }

    playScreen(window);

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /*sprintf_s<100>(data, "%f", clock.getElapsedTime().asSeconds());
        if (socket.send(data, 100, recipient, port) != sf::Socket::Done)
        {
            shape.setFillColor(sf::Color::Red);
        }
        else {

            shape.setFillColor(sf::Color::Green);

        }*/

        window.clear();
        window.draw(shape);
        window.display();
    }

    HttpRequester::getInstance().clean();

    return 0;
}
