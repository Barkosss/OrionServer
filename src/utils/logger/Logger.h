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
    
    static void info(const char* msg);
    static void warning(const char* msg);
    static void error(const char* msg);
    static void debug(const char* msg);
    
    template<typename T>
    static void info(const T& val) {
        std::ostringstream oss;
        oss << val;
        info(oss.str());
    }
    
    template<typename T>
    static void warning(const T& val) {
        std::ostringstream oss;
        oss << val;
        warning(oss.str());
    }
    
    template<typename T>
    static void error(const T& val) {
        std::ostringstream oss;
        oss << val;
        error(oss.str());
    }
    
    template<typename T>
    static void debug(const T& val) {
        std::ostringstream oss;
        oss << val;
        debug(oss.str());
    }
    
    template<typename T>
    static void info(const std::string& text, const T& val) {
        std::ostringstream oss;
        oss << text << val;
        info(oss.str());
    }
    
    template<typename T>
    static void warning(const std::string& text, const T& val) {
        std::ostringstream oss;
        oss << text << val;
        warning(oss.str());
    }
    
    template<typename T>
    static void error(const std::string& text, const T& val) {
        std::ostringstream oss;
        oss << text << val;
        error(oss.str());
    }
    
    template<typename T>
    static void debug(const std::string& text, const T& val) {
        std::ostringstream oss;
        oss << text << val;
        debug(oss.str());
    }

private:
    static bool consoleMode;
    static void log(const std::string& level, const std::string& msg);
    static std::string getTimestamp();
};