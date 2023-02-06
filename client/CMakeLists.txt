cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
project(rtype)

include_directories(ecs/ ecs/components/container ecs/components/content ecs/entity ecs/scene ecs/systems ecs/systems/render ecs/systems/input ecs/systems/storage ecs/system/client)
add_definitions(-Wall -Werror -Wextra -std=c++20)

find_package(SFML 2.5
    COMPONENTS
        system window graphics audio REQUIRED)

find_package(Boost 1.81.0 COMPONENTS system serialization REQUIRED)

add_executable(rtype
    src/GameScene/GameScene.cpp
    src/Core.cpp
    src/main.cpp
)

target_link_libraries(rtype sfml-system sfml-window sfml-graphics sfml-audio Boost::system Boost::serialization)

set_property(TARGET rtype PROPERTY CXX_STANDARD 20)