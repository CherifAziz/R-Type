CMAKE_MINIMUM_REQUIRED(VERSION 3.19)

project(UdpServer LANGUAGES CXX)

set(BIN_NAME udpserver)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${BIN_NAME} main.cpp UdpServer.cpp UdpServer.hpp)

target_include_directories(${BIN_NAME} PUBLIC /opt/homebrew/opt/boost/include)
target_link_directories(${BIN_NAME} PUBLIC /opt/homebrew/opt/boost/lib)
target_link_libraries(${BIN_NAME} -lboost_system)