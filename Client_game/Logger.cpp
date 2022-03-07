#include "Logger.h"

std::map<Logger::LogLevel, std::string> Logger::strLog{

        {Logger::LogLevel::WARN, "WARN"},
        {Logger::LogLevel::ERROR, "ERROR"},
        {Logger::LogLevel::TRACE, "TRACE"},
        {Logger::LogLevel::DEBUG, "DEBUG"},
        {Logger::LogLevel::INFO, "INFO"},
        {Logger::LogLevel::ALL, "ALL"},

};

Logger* Logger::getInstance() {

    static Logger result;
    return &result;

}

Logger::LogLevel Logger::getLogLevelFromStr(std::string level){

    std::string str;
    std::transform(level.begin(), level.end(), std::back_inserter(str), toupper);

    
    for (auto level : strLog) {

        if (str == level.second) {

            return level.first;

        }

    }

    throw str + "- This level of logging does not exist";

}

void Logger::log(std::string message, LogLevel level) {

    std::ofstream file(filename, std::fstream::out | std::fstream::app);
    std::string output;
    output.append(timestamp());
    output.append(" [");
    output.append(strLog.find(level)->second);
    output.append("] ");
    output.append(message);
    output.push_back('\n');
    file << output;
    file.close();

}

std::string Logger::timestamp() {

    const auto& timeZoneDatabase = std::chrono::get_tzdb();
    const auto& currentZone = timeZoneDatabase.current_zone();
    const std::chrono::zoned_time zt{ currentZone->name(), std::chrono::system_clock::now()};

    return std::format("{:%Y-%m-%d %H:%M:%OS}", zt);

}

void Logger::warn(std::string message) {

    if (LogLevel::WARN <= level_) {

        log(message, LogLevel::WARN);
       
    }
    
}



void Logger::error(std::string message) {

    if (LogLevel::ERROR <= level_) {

        log(message, LogLevel::ERROR);

    }

}

void Logger::info(std::string message) {

    if (LogLevel::INFO <= level_) {

        log(message, LogLevel::INFO);

    }

}

void Logger::debug(std::string message) {

    if (LogLevel::DEBUG <= level_) {

        log(message, LogLevel::DEBUG);

    }

}

void Logger::trace(std::string message) {

    if (LogLevel::TRACE <= level_) {

        log(message, LogLevel::TRACE);

    }

}

void Logger::all(std::string message) {

    if (LogLevel::ALL <= level_) {

        log(message, LogLevel::ALL);

    }

}

void Logger::setLevel(LogLevel level){

    level_ = level;

}