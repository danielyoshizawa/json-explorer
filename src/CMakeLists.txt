cmake_minimum_required(VERSION 3.14)

set(NAME "json-explorer")

project("${NAME}" CXX)

set(CMAKE_BUILD_TYPE Debug)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

find_package(CURL REQUIRED)
find_package(simdjson REQUIRED)

add_executable("${NAME}" main.cpp)
target_sources("${NAME}" PUBLIC explorer.cpp)
target_link_libraries("${NAME}" CURL::libcurl simdjson)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD_REQUIRED YES)

include(CTest)

add_subdirectory(test)

add_test(NAME test COMMAND json-explorer-test)
