#include "InputWindow.h"

InputWindow::InputWindow(sf::Font& font):
    font_{font},
    string_{},
    isFocused_{ false },
    cursorTextPosition_{ 0U },
    startStringIndex_{ 0U },
    offset_{0.f},
    isEnterPressed_{ false },
    state_{ 0 },
    numberCharacter_{ 0 },
    cursorWidth_{ 1.5f },
    cursorPosition_{ 0.f },
    height_{ 0.f }
{

    text_.setFont(font_);

}

bool InputWindow::isFocusedCheck(sf::Event& event, const sf::Vector2f & mousePosition){

    bool isLeftMousePressed = event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (frame_.getLocalBounds().contains(mousePosition-this->getPosition())) {

        if (!isFocused_) {

            isFocused_ = isLeftMousePressed;

        }

    }
    else if(isFocused_ && isLeftMousePressed) {

        isFocused_ = false;

    }

    return isFocused_;

}

bool InputWindow::isFocused(){

    return false;

}

void InputWindow::lostFocus(){

    isEnterPressed_ = false;
    isFocused_ = false;

}

void InputWindow::updateByEvent(sf::Event& event){

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && cursorTextPosition_ > 0) {
        
        cursorTextPosition_--;

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && cursorTextPosition_ < string_.getSize()) {

        cursorTextPosition_++;

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) &&
        (string_.getSize() > 0 && cursorTextPosition_ < string_.getSize())) 
    {
        
        string_ = string_.substring(0, cursorTextPosition_) + string_.substring(cursorTextPosition_ + 1);

    }
    else if (event.type == sf::Event::TextEntered && isFocused_ && event.text.unicode < 128) {


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {

            backspace();

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

            isEnterPressed_ = true;

        }
        else if (event.text.unicode >= 32) {

            string_ = string_.substring(0, cursorTextPosition_) + event.text.unicode + string_.substring(cursorTextPosition_);
            cursorTextPosition_++;

        }

    }

    if (cursorTextPosition_ > numberCharacter_ + startStringIndex_) {

        startStringIndex_++;

    }
    else if (cursorTextPosition_ < startStringIndex_) {

        startStringIndex_--;

    }

    setPositions();

    text_.setString(string_.substring(startStringIndex_, numberCharacter_));

}

void InputWindow::update(){

    static bool phase{ true };
    sf::Color cursorColor;
    if(phase) {

        cursorColor.r = 5 + 0.9 * (text_.getFillColor().r * frame_.getFillColor().r) / 255;
        cursorColor.g = 5 + 0.9 * (text_.getFillColor().g * frame_.getFillColor().g) / 255;
        cursorColor.b = 5 + 0.9 * (text_.getFillColor().b * frame_.getFillColor().b) / 255;
        cursorColor.a = 193;

    }
    else if (isFocused_) {

        cursorColor.r ^= cursorColor.r;
        cursorColor.g ^= cursorColor.g;
        cursorColor.b ^= cursorColor.b;

    }

    if (clock_.getElapsedTime().asMilliseconds() > 730) {

        phase = !phase;
        clock_.restart();

    }

    cursor_.setFillColor(cursorColor);

}

void InputWindow::setFrameSize(const sf::Vector2f& size){

    frame_.setSize(size);
    state_ |= 1;
    setTextParameters();

}

void InputWindow::setFrameColor(const sf::Color& color){

    frame_.setFillColor(color);

}

void InputWindow::setFrameOutlineColor(const sf::Color& color){

    frame_.setOutlineColor(color);

}

void InputWindow::setFrameOutlineThickness(float thickness){

    frame_.setOutlineThickness(thickness);

}

void InputWindow::setCharacterSize(size_t size){

    text_.setCharacterSize(size);
    state_ |= 2;
    setTextParameters();

}

void InputWindow::setTextColor(const sf::Color& color){

    text_.setFillColor(color);

}

void InputWindow::setTextOutlineColor(const sf::Color& color){

    text_.setOutlineColor(color);

}

void InputWindow::setTextOutlineThickness(float thickness){

    text_.setOutlineThickness(thickness);

}

bool InputWindow::isEnterPressed() const{

    return isEnterPressed_;

}

sf::String InputWindow::getString() const{

    return string_;

}

void InputWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    states.transform *= getTransform();

    target.draw(frame_, states);
    target.draw(text_, states);
    target.draw(cursor_, states);

}

void InputWindow::setTextParameters(){

    if (state_ == 3) {

        float maxW = -1;
        float maxH = -1;
        sf::Uint32 symbol = 0;
        for (size_t i = 32; i < 128; i++) {

            auto g = font_.getGlyph(i, text_.getCharacterSize(), text_.getStyle() & sf::Text::Bold, text_.getOutlineThickness());

            if (g.bounds.width > maxW) {

                maxW = g.bounds.width;
                symbol = i;

            }

            if (g.bounds.height > maxH) {

                maxH = g.bounds.height;

            }

        }

        height_ = maxH;
        numberCharacter_ = floor(frame_.getLocalBounds().width / maxW);
       
        sf::String tempString;
        for (size_t i{ 0 }; i < numberCharacter_;i++) {

            tempString +=symbol;

        }
        text_.setString(tempString);
        offset_ = abs(frame_.getLocalBounds().width - text_.getGlobalBounds().width) / 2;
        text_.setString(sf::String{});


    }

}

void InputWindow::backspace(){

    if (string_.getSize() > 0 && cursorTextPosition_ > 0) {

        string_ = string_.substring(0, cursorTextPosition_ - 1) + string_.substring(cursorTextPosition_);
        cursorTextPosition_--;

        if (startStringIndex_ == cursorTextPosition_) {

            while (cursorTextPosition_ - startStringIndex_ < numberCharacter_ && startStringIndex_ > 0) {
                startStringIndex_--;
            }

        }

    }

}

void InputWindow::setPositions(){

    text_.setString(string_.substring(startStringIndex_, cursorTextPosition_ - startStringIndex_));
    cursorPosition_ = text_.getGlobalBounds().width;

    auto offsetKerning = 0;
    if (cursorTextPosition_ < string_.getSize() && cursorTextPosition_>0) {

        offsetKerning = font_.getKerning(string_[cursorTextPosition_ - 1], string_[cursorTextPosition_], text_.getCharacterSize());

    }

    text_.setPosition(sf::Vector2f(offset_, frame_.getGlobalBounds().height / 2 - height_ + text_.getOutlineThickness()));

    cursor_.setSize(sf::Vector2f(cursorWidth_, frame_.getSize().y));
    cursor_.setPosition(sf::Vector2f(cursorPosition_ + offset_ + text_.getCharacterSize()/10 + offsetKerning - cursor_.getSize().x / 2, 0));

}
