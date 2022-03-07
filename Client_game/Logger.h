#pragma once
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <chrono>
#include <ctime>

class Logger {
public: 

	enum class logLevel { WARN, ERROR, INFO, DEBUG, TRACE, ALL };
	static Logger* getInstance();
	static logLevel getLogLevelFromStr(std::string str);
	void log(std::string message, logLevel level);
	std::string timestamp();

	void warn(std::string message);
	void error(std::string message);
	void info(std::string message);
	void debug(std::string message);
	void trace(std::string message);
	void all(std::string message);

	void setLevel(logLevel level);

	const std::map<logLevel, std::string> strLog
	{
		{Logger::logLevel::WARN, " [WARN] "}, 
		{Logger::logLevel::ERROR, " [ERROR] "}, 
		{Logger::logLevel::TRACE, " [TRACE] "},  
		{Logger::logLevel::DEBUG, " [DEBUG] "}, 
		{Logger::logLevel::INFO, " [INFO] "}, 
		{Logger::logLevel::ALL, " [ALL] "},
	};

private:

	Logger() {};
	std::string filename = "Client_game.log";
    logLevel level_;
	
};