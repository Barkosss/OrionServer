cmake_minimum_required(VERSION 4.0)
project(MSLauncher)

set(CMAKE_CXX_STANDARD 20)

add_executable(MSLauncher src/main.cpp
        src/config/Config.cpp
        src/config/Config.h
        src/utils/logger/Logger.cpp
        src/utils/logger/Logger.h)
