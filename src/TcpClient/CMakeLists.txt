CMAKE_MINIMUM_REQUIRED(VERSION 3.19)

project(Client LANGUAGES CXX)


set(BIN_NAME tcpclient)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${BIN_NAME} main.cpp Client/Client.cpp Client/Client.hpp)

set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 17)
target_include_directories(${BIN_NAME} PUBLIC ./Client)

find_package(Boost REQUIRED COMPONENTS system serialization)
target_link_libraries(${BIN_NAME} PRIVATE Boost::serialization Boost::system)

# target_include_directories(${BIN_NAME} PUBLIC /opt/homebrew/opt/boost/include)
# target_link_directories(${BIN_NAME} PUBLIC /opt/homebrew/opt/boost/lib)
# target_link_libraries(${BIN_NAME} -lboost_system -lboost_serialization -pthread)
