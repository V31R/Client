#include "SettingsProfileLoader.h"

#define BUFFER_SIZE 255

SettingsProfileLoader::Property SettingsProfileLoader::currentProperty{ SettingsProfileLoader::Property::NOTHING };
SettingsProfileLoader::State SettingsProfileLoader::currentState{ SettingsProfileLoader::State::NOTHING };

SettingsProfile SettingsProfileLoader::load(){

    std::ifstream input{ "app.settings" };

    SettingsProfile result{ 54000, "127.0.0.1"};

    while (!input.eof()) {

        char buffer[BUFFER_SIZE]="";
        input.getline(buffer, BUFFER_SIZE);

        if (*buffer) {

            size_t i{ 0 };
            while (i < BUFFER_SIZE && buffer[i]) {

                void * data = nullptr;

                switchFileSymbol(buffer, i);
                getProperty(data, buffer, i);
                setProperty(result, data);
                switchFileSymbol(buffer, i);
               
                if (data) {

                    delete data;

                }

            }

        }

    }


    return result;

}

void SettingsProfileLoader::switchFileSymbol(char* buffer, size_t& i) {

    while (i < BUFFER_SIZE && buffer[i] <= ' ' && currentState != State::READ) {

        i++;

    }

    if (i < BUFFER_SIZE && buffer[i] == '<' && currentState == State::NOTHING) {

        currentState = State::START;
        do {

            i++;

        } while (i < BUFFER_SIZE && buffer[i] <= ' ');

    }

    if (i < BUFFER_SIZE && buffer[i] == '<') {

        if (currentState == State::START || currentState == State::END 
            || currentState == State::END_READ) {

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

        currentState = State::END_READ;

        do {

            i++;

        } while (i < BUFFER_SIZE && buffer[i] <= ' ');


    }

    if (i < BUFFER_SIZE && buffer[i] == '>') {

        if (currentProperty == Property::NOTHING) {

            throw std::invalid_argument{ "Expected field name but \">\" was found." };

        }
        else {

            if (currentState == State::START) {

                currentState = State::READ;

            }
            else if (currentState == State::END) {

                currentState = State::NOTHING;
                
            }

        }

        i++;

    }

    if (i < BUFFER_SIZE && buffer[i]>' ') {


        if (currentState == State::START) {

            currentProperty = getPropertyType(buffer, i);

            if (currentProperty == Property::NOTHING) {

                throw std::invalid_argument{ "Expected correct field name." };

            }

        }else if (currentState == State::END_READ) {

            auto endProperty{ getPropertyType(buffer, i) };

            if (currentProperty != endProperty) {

                throw std::invalid_argument{ "Expected correct field name." };

            }

            currentState = State::END;

        }
        else if (currentState == State::READ) {

            return;

        }
 


    }



}

SettingsProfileLoader::Property SettingsProfileLoader::getPropertyType(char* buffer, size_t& i){

    std::string property;

    while (i < BUFFER_SIZE && buffer[i]>' ' && buffer[i] != '>') {

        property += buffer[i];
        i++;

    }

    return getPropertyType(property);

}

SettingsProfileLoader::Property SettingsProfileLoader::getPropertyType(std::string& property) {

    Property result{ Property::NOTHING };

    if (property == "port") {

        result = Property::PORT;

    }else if (property == "ip") {

        result = Property::IP;

    }else if (property == "name") {

        result = Property::NAME;

    }

    return result;

}

void SettingsProfileLoader::getProperty(void *& data, char* buffer, size_t& i){


    if (currentProperty != Property::NOTHING && currentState == State::READ) {

        std::string value;

        while (i < BUFFER_SIZE && buffer[i] != '<') {

            value += buffer[i];
            i++;
        }

        std::istringstream iss{ value };


        switch (currentProperty) {
        case Property::PORT: {

            size_t port;
            iss >> port;
            data = new size_t(port);

            break;

        }
        case Property::IP: {

            std::string ip;
            iss >> ip;
            data = new std::string(ip);

            break;

        }
        case Property::NAME: {

            std::string name;
            iss >> name;
            data = new std::string(name);

            break;

        }

        }

    }

}

void SettingsProfileLoader::setProperty(SettingsProfile & settingProfile, void* data){

    if (currentProperty != Property::NOTHING && currentState == State::READ) {
     
        switch (currentProperty) {
        case Property::PORT: {

            settingProfile.setPort(*reinterpret_cast<size_t *>(data));

            break;

        }
        case Property::IP: {

            settingProfile.setIp(*reinterpret_cast< std::string*>(data));

            break;

        }
        case Property::NAME: {

            settingProfile.setName(*reinterpret_cast<std::string*>(data));

            break;

        }

        }

    }

}



#undef BUFFER_SIZE
