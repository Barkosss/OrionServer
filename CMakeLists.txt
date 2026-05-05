cmake_minimum_required(VERSION 3.31.5)
project(MSLauncher)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BOOST_DIR "F:/tools/vcpkg/installed/x64-windows")
set(Boost_INCLUDE_DIR "${BOOST_DIR}/include")
set(Boost_LIBRARY_DIR "${BOOST_DIR}/lib")

add_executable(MSLauncher
        src/config/Config.cpp
        src/config/Config.h
        src/utils/logger/Logger.cpp
        src/utils/logger/Logger.h
        src/main.cpp
        src/server/Server.cpp
        src/server/Server.h
        src/handlers/file_handler.cpp
        src/handlers/file_handler.h
        src/handlers/health_handler.cpp
        src/handlers/health_handler.h
        src/handlers/manifest_handler.cpp
        src/handlers/manifest_handler.h
        src/handlers/ping_handler.cpp
        src/handlers/ping_handler.h
        src/handlers/sync_handler.cpp
        src/handlers/sync_handler.h
        src/server/Router.cpp
        src/server/Router.h)

set_target_properties(MSLauncher PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(nlohmann_json 3.12.0 REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

target_link_libraries(MSLauncher PRIVATE
        ${Boost_LIBRARIES}
        Threads::Threads
        nlohmann_json::nlohmann_json
        OpenSSL::Crypto
        OpenSSL::SSL
)

target_compile_definitions(MSLauncher PRIVATE
        BOOST_ASIO_HAS_CO_AWAIT
        BOOST_ASIO_NO_DEPRECATED
)

target_include_directories(MSLauncher PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(WIN32)
target_compile_definitions(MSLauncher PRIVATE
        _WIN32_WINNT=0x0A00
        BOOST_ALL_DYN_LINK
)
endif()

if(UNIX AND NOT WIN32)
    target_compile_definitions(MSLauncher PRIVATE
        _GNU_SOURCE
    )
endif()

message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost include: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")