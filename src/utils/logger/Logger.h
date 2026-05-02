//
// Created by Andrey Baryshev on 02.05.2026.
//

#ifndef MSLAUNCHER_LOGGER_H
#define MSLAUNCHER_LOGGER_H

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
    static LogLevel logLevel;

    static void log(const std::string &logLevel, const std::string message);
};


#endif //MSLAUNCHER_LOGGER_H
