//
// Created by Andrey Baryshev on 02.05.2026.
//

#include "Logger.h"

const std::map<LogLevel, std::string> levelToString {
    {LogLevel::INFO, "INFO"},
        {LogLevel::WARNING, "WARNING"},
        {LogLevel::ERROR, "ERROR"},
        {LogLevel::DEBUG, "DEBUG"},
};

LogLevel Logger::logLevel = LogLevel::INFO;

void Logger::log(const std::string &logLevel, const std::string message) {

}