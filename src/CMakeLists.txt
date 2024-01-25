cmake_minimum_required(VERSION 3.14)

set(NAME "json-explorer")

project("${NAME}" CXX)

set(CMAKE_BUILD_TYPE Debug)

add_executable("${NAME}" main.cpp)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD_REQUIRED YES)
