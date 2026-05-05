#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

class Logger {
private:
    static bool consoleMode;
    static void log(const std::string& level, const std::string& msg);
    static std::string getTimestamp();

    template<typename T>
    static std::string formatString(const std::string& format, const T& val) {
        size_t pos = format.find("{}");
        if (pos == std::string::npos) {
            return format;
        }
        
        std::string result = format.substr(0, pos);
        
        std::ostringstream oss;
        oss << val;
        result += oss.str();
        
        result += format.substr(pos + 2);
        return result;
    }

    static std::string formatString(const std::string& format) {
        return format;
    }

    template<typename First, typename... Rest>
    static std::string formatString(const std::string& format, First&& first, Rest&&... rest) {
        size_t pos = format.find("{}");
        
        if (pos == std::string::npos) {
            std::ostringstream oss;
            oss << format;
            ((oss << std::forward<Rest>(rest)), ...);
            return oss.str();
        }
        
        std::string result = format.substr(0, pos);
        
        std::ostringstream oss;
        oss << std::forward<First>(first);
        result += oss.str();
        
        result += formatString(format.substr(pos + 2), std::forward<Rest>(rest)...);
        
        return result;
    }

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

    template<typename... Args>
    static void info(const std::string& format, Args&&... args) {
        info(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void warning(const std::string& format, Args&&... args) {
        warning(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void error(const std::string& format, Args&&... args) {
        error(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void debug(const std::string& format, Args&&... args) {
        debug(formatString(format, std::forward<Args>(args)...));
    }
};