#include "SettingsProfileLoader.h"

SettingsProfileLoader::Property SettingsProfileLoader::currentProperty{ SettingsProfileLoader::Property::NOTHING };
SettingsProfileLoader::State SettingsProfileLoader::currentState{ SettingsProfileLoader::State::NOTHING };

SettingsProfile SettingsProfileLoader::load(){
#define BUFFER_SIZE 255
    std::ifstream input{ "app.settings" };

    SettingsProfile result{};

    while (!input.eof()) {

        wchar_t symbol;
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

void SettingsProfileLoader::switchFileSymbol(char* buffer, size_t& i){

   if (buffer[i] == '<' && State::NOTHING){

        currentState = State::START;
        while( buffer[++i] <= ' ' );
        getPropertyType(buffer, i);

   }
   else if (buffer[i] == '<' && State::READ) {

       currentState = State::END;
       while (buffer[++i] <= ' ');

       do {

           i++;

       }
       while (buffer[i] <= ' ' || buffer[i] =='/');

       getPropertyType(buffer, i);

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
