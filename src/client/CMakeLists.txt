CMAKE_MINIMUM_REQUIRED(VERSION 3.19)

project(rtypeclient LANGUAGES CXX)

set(BIN_NAME r-type_client)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${BIN_NAME} test_client.cpp)

set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 17)

find_package(SFML COMPONENTS system window graphics network audio CONFIG REQUIRED)
target_link_libraries(${BIN_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)