#pragma once
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <chrono>
#include <sstream>
#include <iostream>
#include<format>
//#include <ctime>

class Logger {
public: 

	enum class LogLevel { WARN, ERROR, INFO, DEBUG, TRACE, ALL };
	static Logger* getInstance();
	static LogLevel getLogLevelFromStr(std::string str);
	void log(std::string message, LogLevel level);
	std::string timestamp();

	void warn(std::string message);
	void error(std::string message);
	void info(std::string message);
	void debug(std::string message);
	void trace(std::string message);
	void all(std::string message);

	void setLevel(LogLevel level);

	static std::map<LogLevel, std::string> strLog;
	

private:

	Logger() {};
	std::string filename = "Client_game.log";
    LogLevel level_;
	
};