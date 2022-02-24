#pragma once
#include "SettingsProfile.h"
#include <fstream>
#include <sstream>


class SettingsProfileLoader{

public:

	static SettingsProfile load();

private:

	enum Property { NOTHING, PORT, IP, NAME };
	enum State { NOTHING, START, READ, END };

	static void switchFileSymbol(char* buffer, size_t & i);
	static void getPropertyType(char* buffer, size_t& i);
	static void getProperty(void*& data, char* buffer, size_t& i);
	static void setProperty(SettingsProfile & settingProfile, void*& data);
	static Property getPropertyType(std::string& property);

	static Property currentProperty;
	static State currentState;

};

