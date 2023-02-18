cmake_minimum_required(VERSION 3.17)
project(rtype LANGUAGES CXX)
set(BIN_NAME rtype)
set(CMAKE_CXX_STANDARD 20)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_BINARY_DIR $ENV{ROOT_DIR}/build/Release)
endif ()
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
include_directories($ENV{ROOT_DIR}/ecs/ $ENV{ROOT_DIR}/ecs/components/container/ $ENV{ROOT_DIR}/ecs/components/content/ $ENV{ROOT_DIR}/ecs/entity/ $ENV{ROOT_DIR}/ecs/scene/ $ENV{ROOT_DIR}/ecs/systems/ $ENV{ROOT_DIR}/ecs/core/ $ENV{ROOT_DIR}/ecs/systems/render/ $ENV{ROOT_DIR}/ecs/systems/input/ $ENV{ROOT_DIR}/ecs/storage/ $ENV{ROOT_DIR}/src/ $ENV{ROOT_DIR}/src/GameScene/ $ENV{ROOT_DIR}/ecs/systems/game/)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)

add_executable(${BIN_NAME}
GameScene/GameScene.cpp
GameScene/PlayerBullet.cpp
GameScene/BasicEnemy.cpp
Core.cpp
main.cpp
)

target_link_libraries(${BIN_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 20)