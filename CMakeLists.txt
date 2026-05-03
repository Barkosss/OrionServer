cmake_minimum_required(VERSION 3.31.5)
project(MSLauncher)

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
        src/server/Server.h)

find_package(Boost REQUIRED COMPONENTS filesystem system asio)
find_package(Threads REQUIRED)

target_link_libraries(MSLauncher PRIVATE
        ${Boost_LIBRARIES}
        Threads::Threads
        Boost::asio
        Boost::filesystem
        Boost::system
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

message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost include: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")