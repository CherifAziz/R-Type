cmake_minimum_required(VERSION 3.17)

project(rtype LANGUAGES CXX)

set(BIN_NAME r-type_client)
set(CMAKE_CXX_STANDARD 20)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ROOT_DIR}/build/Release)
endif ()
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
find_package(Boost COMPONENTS system serialization REQUIRED)

include_directories(Services/ GameScene/ GameScene/Menu GameScene/Enemy GameScene/Enemy/Basic GameScene/Enemy/Boss GameScene/Enemy/Fly GameScene/Enemy/Medium GameScene/Enemy/Vessel)

set(GAMESCENE_FILES 
    GameScene/GameScene.cpp 
    GameScene/PlayerBullet.cpp 
    GameScene/Menu/HomeMenuScene.cpp 
    GameScene/Menu/SettingsMenu.cpp 
    GameScene/Enemy/EnemyBullet.cpp 
    GameScene/Enemy/EnemyManager.cpp 
    GameScene/Enemy/Basic/BasicEnemy.cpp 
    GameScene/Enemy/Fly/FlyEnemy.cpp 
    GameScene/Enemy/Boss/BossEnemy.cpp 
    GameScene/Enemy/Medium/MediumEnemy.cpp 
    GameScene/Enemy/Vessel/VesselEnemy.cpp
)
set(SERVICES_FILES Services/Services.cpp)


# set(GAMESCENE_FILES GameScene/GameScene.cpp GameScene/PlayerBullet.cpp)
# set(SERVICES_FILES Services/Services.cpp)

add_executable(${BIN_NAME}
${GAMESCENE_FILES}
${SERVICES_FILES}
Core.cpp
main.cpp
)

target_link_libraries(${BIN_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio Boost::system Boost::serialization)
set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 20)