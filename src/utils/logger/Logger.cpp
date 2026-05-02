//
// Created by Andrey Baryshev on 02.05.2026.
//

#include "Logger.h"
#include <format>
#include <iostream>
#include <ostream>

const std::map<LogLevel, std::string> levelToString{
    {LogLevel::INFO, "INFO"},
    {LogLevel::WARNING, "WARNING"},
    {LogLevel::ERROR, "ERROR"},
    {LogLevel::DEBUG, "DEBUG"},
};

LogLevel Logger::logLevel = LogLevel::INFO;
bool Logger::consoleMode = false;

void Logger::setConsoleMode(const bool enable) {
    consoleMode = enable;
}

void Logger::log(LogLevel logLevel, const std::string& message) {
    if (consoleMode) {
        std::cout << "[" << levelToString.at(logLevel) << "] " << message << std::endl;
    }
}

template<typename ...Args>
void Logger::info(const std::string& format, const Args&... args) {
    log(LogLevel::INFO, std::format(format, args...));
}

template<typename ...Args>
void Logger::warning(const std::string& format, const Args&... args) {
    log(LogLevel::WARNING, std::format(format, args...));
}
template<typename ...Args>
void Logger::error(const std::string& format, const Args&... args) {
    log(LogLevel::ERROR, std::format(format, args...));
}
template<typename ...Args>
void Logger::debug(const std::string& format, const Args&... args) {
    log(LogLevel::DEBUG, std::format(format, args...));
}