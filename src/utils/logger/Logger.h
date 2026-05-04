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

    static void info(const std::string& text, const char* val) {
        info(text + std::string(val));
    }
    
    static void warning(const std::string& text, const char* val) {
        warning(text + std::string(val));
    }
    
    static void error(const std::string& text, const char* val) {
        error(text + std::string(val));
    }
    
    static void debug(const std::string& text, const char* val) {
        debug(text + std::string(val));
    }

    static void info(const std::string& text, bool val) {
        info(text + (val ? "true" : "false"));
    }
    
    static void warning(const std::string& text, bool val) {
        warning(text + (val ? "true" : "false"));
    }
    
    static void error(const std::string& text, bool val) {
        error(text + (val ? "true" : "false"));
    }
    
    static void debug(const std::string& text, bool val) {
        debug(text + (val ? "true" : "false"));
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

    static void info(const std::string& text, const std::string& val) {
        info(text + val);
    }
    
    static void warning(const std::string& text, const std::string& val) {
        warning(text + val);
    }
    
    static void error(const std::string& text, const std::string& val) {
        error(text + val);
    }
    
    static void debug(const std::string& text, const std::string& val) {
        debug(text + val);
    }

    template<typename... Args>
    static void info(const std::string& format, Args&... args) {
        info(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void warning(const std::string& format, Args&... args) {
        warning(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void error(const std::string& format, Args&... args) {
        error(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void debug(const std::string& format, Args&... args) {
        debug(formatString(format, std::forward<Args>(args)...));
    }

private:
    static bool consoleMode;
    static void log(const std::string& level, const std::string& msg);
    static std::string getTimestamp();

    static std::string formatString(const std::string& format);

    template<typename First, typename... Rest>
    static std::string formatString(const std::string& format, First&& first, Rest&&... rest) {
        std::string result;
        std::string::size_type pos = 0;
        std::string::size_type placeholder = format.find("{}", pos);

        if (placeholder == std::string::npos) {
            return format;
        }

        result.append(format, pos, placeholder - pos);

        std::ostringstream oss;
        oss << first;
        result += oss.str();

        std::string remaining = format.substr(placeholder + 2);
        result += formatString(remaining, std::forward<Rest>(rest)...);

        return result;
    }
};