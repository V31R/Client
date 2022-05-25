#include "DataLoadScreen.h"

void DataLoadScreen::show(sf::RenderWindow& window, int* state){

    sf::Font font;
    font.loadFromFile("fonts/consola.ttf");

    sf::Clock clock;
    sf::String textString = "Loading files";
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);

    size_t k{ 0 };
    while (window.isOpen() && *state == 0) {

        if (clock.getElapsedTime().asMilliseconds() > 800) {

            if (k >= 3) {

                k = 0;
            }
            else {

                k++;

            }

            clock.restart();

        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::String dots;
        for (size_t i{ 0 }; i < k; i++) {

            dots += ".";

        }
        text.setString(textString + dots);


        text.setPosition(sf::Vector2f(window.getSize()) / 2.f - sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) / 2.f);
        window.clear();
        window.draw(text);
        window.display();
    }

}
