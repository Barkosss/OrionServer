//
// Created by Andrey Baryshev on 02.05.2026.
//
#pragma once

#ifndef MSLAUNCHER_LOGGER_H
#define MSLAUNCHER_LOGGER_H

#include<string>
#include<map>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

extern const std::map<LogLevel, std::string> levelToString;

class Logger {
    static LogLevel logLevel;

    static void log(const std::string &logLevel, const std::string message);

public:

    template<typename... Args>
    static void info(const std::string &format, const Args &...args);

    template <typename... Args>
    static void warning(const std::string &format, const Args &...args);

    template <typename... Args>
    static void error(const std::string &format, const Args &...args);

    template <typename... Args>
    static void debug(const std::string &format, const Args &...args);
};


#endif //MSLAUNCHER_LOGGER_H
