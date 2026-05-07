include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    test_config.cpp
)

set_target_properties(run_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

find_package(nlohmann_json 3.12.0 REQUIRED)

target_include_directories(run_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(run_tests PRIVATE
    MSBackend
    gtest_main
    nlohmann_json::nlohmann_json
)