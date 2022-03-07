#include "Logger.h"

std::map<Logger::logLevel, std::string> Logger::strLog{

        {Logger::logLevel::WARN, "WARN"},
        {Logger::logLevel::ERROR, "ERROR"},
        {Logger::logLevel::TRACE, "TRACE"},
        {Logger::logLevel::DEBUG, "DEBUG"},
        {Logger::logLevel::INFO, "INFO"},
        {Logger::logLevel::ALL, "ALL"},

};

Logger* Logger::getInstance() {

    static Logger result;
    return &result;

}

Logger::logLevel Logger::getLogLevelFromStr(std::string level){

    std::string str;
    std::transform(level.begin(), level.end(), std::back_inserter(str), toupper);

    
    for (auto level : strLog) {

        if (str == level.second) {

            return level.first;

        }

    }

    throw str + "- This level of logging does not exist";

}

void Logger::log(std::string message, logLevel level) {

    std::ofstream file(filename,std::ios_base::app);
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
    
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(tp);
    std::tm gmt{}; gmtime_s(&gmt, &tt);
    std::chrono::duration<double> fractional_seconds =
        (tp - std::chrono::system_clock::from_time_t(tt)) + std::chrono::seconds(gmt.tm_sec);
    
    std::string buffer("year/mo/dy hr:mn:sc.xxxxxx");
#pragma warning(suppress : 4996)
    sprintf(&buffer.front(), "%04d/%02d/%02d %02d:%02d:%09.6f", gmt.tm_year + 1900, gmt.tm_mon + 1,
        gmt.tm_mday, gmt.tm_hour, gmt.tm_min, fractional_seconds.count());
    
    return buffer;
}

void Logger::warn(std::string message) {

    if (logLevel::WARN <= level_) {

        log(message, logLevel::WARN);
       
    }
    
}



void Logger::error(std::string message) {

    if (logLevel::ERROR <= level_) {

        log(message, logLevel::ERROR);

    }

}

void Logger::info(std::string message) {

    if (logLevel::INFO <= level_) {

        log(message, logLevel::INFO);

    }

}

void Logger::debug(std::string message) {

    if (logLevel::DEBUG <= level_) {

        log(message, logLevel::DEBUG);

    }

}

void Logger::trace(std::string message) {

    if (logLevel::TRACE <= level_) {

        log(message, logLevel::TRACE);

    }

}

void Logger::all(std::string message) {

    if (logLevel::ALL <= level_) {

        log(message, logLevel::ALL);

    }

}

void Logger::setLevel(logLevel level){

    level_ = level;

}