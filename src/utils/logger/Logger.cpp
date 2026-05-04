#include "Logger.h"

bool Logger::consoleMode = true;

void Logger::setConsoleMode(bool enable) {
    consoleMode = enable;
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    struct tm time_info;
    
    #ifdef _WIN32
        localtime_s(&time_info, &now_time);
    #else
        localtime_r(&now_time, &time_info);
    #endif
    
    std::ostringstream oss;
    oss << std::put_time(&time_info, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::log(const std::string& level, const std::string& msg) {
    if (consoleMode) {
        std::cout << "[" << getTimestamp() << "] [" << level << "] " << msg << std::endl;
    }
}

void Logger::info(const std::string& msg) { log("INFO", msg); }
void Logger::warning(const std::string& msg) { log("WARNING", msg); }
void Logger::error(const std::string& msg) { log("ERROR", msg); }
void Logger::debug(const std::string& msg) { log("DEBUG", msg); }

void Logger::info(const char* msg) { info(std::string(msg)); }
void Logger::warning(const char* msg) { warning(std::string(msg)); }
void Logger::error(const char* msg) { error(std::string(msg)); }
void Logger::debug(const char* msg) { debug(std::string(msg)); }