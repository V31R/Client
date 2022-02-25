#include "SettingsProfileLoader.h"

SettingsProfileLoader::Property SettingsProfileLoader::currentProperty{ SettingsProfileLoader::Property::NOTHING };
SettingsProfileLoader::State SettingsProfileLoader::currentState{ SettingsProfileLoader::State::NOTHING };

SettingsProfile SettingsProfileLoader::load(){
#define BUFFER_SIZE 255
    std::ifstream input{ "app.settings" };

    SettingsProfile result{};

    while (!input.eof()) {

        char buffer[BUFFER_SIZE];
        input.getline(buffer, BUFFER_SIZE);

        if (!input.eof()) {

            size_t i{ 0 };
            while (buffer[i]) {

                void * data;

                switchFileSymbol(buffer, i);
                getProperty(data, buffer, i);
                setProperty(result, data);

                delete data;

            }

        }

    }


    return result;

}

void SettingsProfileLoader::switchFileSymbol(char* buffer, size_t& i) {

    while (i < BUFFER_SIZE && buffer[i] <= ' ') {

        i++;

    }

    if (i < BUFFER_SIZE && buffer[i] == '<' && currentState == State::NOTHING) {

        currentState = State::START;
        do {

            i++;

        } while (i < BUFFER_SIZE && buffer[i] <= ' ');

    }

    if (i < BUFFER_SIZE && buffer[i] == '<') {

        if (currentState == State::START || currentState == State::END) {

            throw std::invalid_argument{"Expected field name but \"<\" was found."};

        }

        if (currentState == State::READ) {

            currentState = State::END;
            do {

                i++;

            } while (i < BUFFER_SIZE && buffer[i] <= ' ');

        }

    }

    if (i < BUFFER_SIZE && buffer[i] == '/' && currentState == State::END) {

        do {

            i++;

        } while (i < BUFFER_SIZE && buffer[i] <= ' ');


    }



    if (i < BUFFER_SIZE && buffer[i] == '>') {


    }


}

void SettingsProfileLoader::getPropertyType(char* buffer, size_t& i){



}

SettingsProfileLoader::Property SettingsProfileLoader::getPropertyType(std::string& property) {

    return Property();

}

void SettingsProfileLoader::getProperty(void*& data, char* buffer, size_t& i){



}

void SettingsProfileLoader::setProperty(SettingsProfile & settingProfile, void*& data){



}



#undef BUFFER_SIZE
