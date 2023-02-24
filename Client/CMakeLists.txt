cmake_minimum_required(VERSION 3.17)

project(rtype LANGUAGES CXX)

set(BIN_NAME r-type_client)
set(CMAKE_CXX_STANDARD 17)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ROOT_DIR}/build/Release)
endif ()
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
find_package(Boost COMPONENTS system serialization REQUIRED)

include_directories(Services/ GameScene/)

set(GAMESCENE_FILES GameScene/GameScene.cpp GameScene/PlayerBullet.cpp GameScene/BasicEnemy.cpp GameScene/MediumEnemy.cpp)
set(SERVICES_FILES Services/Services.cpp)

add_executable(${BIN_NAME}
${GAMESCENE_FILES}
${SERVICES_FILES}
Core.cpp
main.cpp
)

target_link_libraries(${BIN_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio Boost::system Boost::serialization)
set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 17)