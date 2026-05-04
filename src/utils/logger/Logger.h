#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

class Logger {
public:
    static void setConsoleMode(bool enable);
    
    static void info(const std::string& msg);
    static void warning(const std::string& msg);
    static void error(const std::string& msg);
    static void debug(const std::string& msg);
    
    static void info(int val);
    static void warning(int val);
    static void error(int val);
    static void debug(int val);
    
    static void info(const char* msg);
    static void warning(const char* msg);
    static void error(const char* msg);
    static void debug(const char* msg);
    
    template<typename T>
    static void info(const T& val) {
        info(std::to_string(val));
    }
    
    template<typename T>
    static void warning(const T& val) {
        warning(std::to_string(val));
    }
    
    template<typename T>
    static void error(const T& val) {
        error(std::to_string(val));
    }
    
    template<typename T>
    static void debug(const T& val) {
        debug(std::to_string(val));
    }
    
    static void info(const std::string& text, int val) {
        info(text + std::to_string(val));
    }
    
    static void warning(const std::string& text, int val) {
        warning(text + std::to_string(val));
    }
    
    static void error(const std::string& text, int val) {
        error(text + std::to_string(val));
    }
    
    static void info(const std::string& text, const std::string& val) {
        info(text + val);
    }
    
    static void warning(const std::string& text, const std::string& val) {
        warning(text + val);
    }
    
    static void error(const std::string& text, const std::string& val) {
        error(text + val);
    }
    
    static void info(const std::string& text, const char* val) {
        info(text + std::string(val));
    }
    
    static void warning(const std::string& text, const char* val) {
        warning(text + std::string(val));
    }
    
    static void error(const std::string& text, const char* val) {
        error(text + std::string(val));
    }
    
    template<typename T>
    static void info(const std::string& text, const T& val) {
        info(text + std::to_string(val));
    }
    
    template<typename T>
    static void warning(const std::string& text, const T& val) {
        warning(text + std::to_string(val));
    }
    
    template<typename T>
    static void error(const std::string& text, const T& val) {
        error(text + std::to_string(val));
    }

private:
    static bool consoleMode;
    static void log(const std::string& level, const std::string& msg);
    static std::string getTimestamp();
};