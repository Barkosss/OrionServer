//
// Created by Andrey Baryshev on 02.05.2026.
//

#ifndef MSLAUNCHER_CONFIG_H
#define MSLAUNCHER_CONFIG_H

#include<string>
#include<fstream>

class Config {
    std::string logFilename;
    std::fstream logFile;

public:
    Config();
    ~Config();

    std::string getLogFilename();
    void setLogFilename(std::string logFilename);
    std::fstream getLogFile();
};


#endif //MSLAUNCHER_CONFIG_H
