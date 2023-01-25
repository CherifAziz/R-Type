cmake_minimum_required(VERSION 3.16)
project(game)

include(r-type/conanbuildinfo.cmake)
find_package(sfml REQUIRED)

add_executable(game gametest.cpp)

target_link_libraries(test_project PRIVATE
  sfml::sfml)