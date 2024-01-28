cmake_minimum_required(VERSION 3.14)

set(NAME "json-explorer-test")

add_executable("${NAME}" example.test.cpp)
target_sources("${NAME}" PUBLIC explorer.test.cpp simdjson.test.cpp)
target_sources("${NAME}" PRIVATE ../model/explorer/explorer.cpp)
target_link_libraries("${NAME}" PRIVATE Catch2::Catch2WithMain simdjson)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD_REQUIRED YES)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
