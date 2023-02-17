cmake_minimum_required(VERSION 3.17)

project(rtype LANGUAGES CXX)

set(BIN_NAME r-type_server)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(SFML COMPONENTS system window graphics audio REQUIRED)
find_package(Boost 1.74.0 COMPONENTS system serialization thread REQUIRED)

add_executable(${BIN_NAME}
GameScene/GameScene.cpp
GameScene/PlayerBullet.cpp
GameScene/BasicEnemy.cpp
Core.cpp
main.cpp
)

target_link_libraries(${BIN_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio Boost::system Boost::serialization Boost::thread)
set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 20)