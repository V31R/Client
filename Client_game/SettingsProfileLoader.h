#pragma once
#include "SettingsProfile.h"
#include <exception>
#include <fstream>
#include <sstream>


class SettingsProfileLoader{

public:

	static SettingsProfile load();

private:

	enum class Property { NOTHING, PORT, IP, NAME };
	enum class State { NOTHING, START, READ, END, END_READ };

	static void switchFileSymbol(char* buffer, size_t & i);
	static void getPropertyType(char* buffer, size_t& i);
	static void getProperty(void*& data, char* buffer, size_t& i);
	static void setProperty(SettingsProfile & settingProfile, void*& data);
	static Property getPropertyType(std::string& property);

	static Property currentProperty;
	static State currentState;

};

