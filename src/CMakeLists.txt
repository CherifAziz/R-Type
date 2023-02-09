cmake_minimum_required(VERSION 3.17)
project(rtype LANGUAGES CXX)
set(BIN_NAME rtype)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories($ENV{ROOT_DIR}/ecs/ $ENV{ROOT_DIR}/ecs/components/container/ $ENV{ROOT_DIR}/ecs/components/content/ $ENV{ROOT_DIR}/ecs/entity $ENV{ROOT_DIR}/ecs/scene/ $ENV{ROOT_DIR}/ecs/systems/ $ENV{ROOT_DIR}/ecs/systems/render/ $ENV{ROOT_DIR}/ecs/systems/input/ $ENV{ROOT_DIR}/ecs/systems/storage/)
# add_definitions(-Wall -WX -Wextra -std=c++20)
# set(SFML_ROOT $ENV{ROOT_DIR}/vcpkg/packages/sfml_x86-windows/)
# set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/module" "${CMAKE_MODULE_PATH}")
find_package(SFML COMPONENTS system window graphics audio REQUIRED)

add_executable(${BIN_NAME}
GameScene/GameScene.cpp
GameScene/PlayerBullet.cpp
GameScene/BasicEnemy.cpp
Core.cpp
main.cpp
)

target_link_libraries(${BIN_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 17)