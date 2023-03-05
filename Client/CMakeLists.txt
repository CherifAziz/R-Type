cmake_minimum_required(VERSION 3.17)

project(rtype LANGUAGES CXX)

set(BIN_NAME r-type_client)
set(CMAKE_CXX_STANDARD 20)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
    set(ECS_FILES
        $ENV{ROOT_DIR}/ecs/components/container/ComponentManager.cpp
        $ENV{ROOT_DIR}/ecs/components/content/Action.cpp
        $ENV{ROOT_DIR}/ecs/components/content/Animation.cpp
        $ENV{ROOT_DIR}/ecs/components/content/Movement.cpp
        $ENV{ROOT_DIR}/ecs/components/content/Sprite.cpp
        $ENV{ROOT_DIR}/ecs/entity/EntityManager.cpp
        $ENV{ROOT_DIR}/ecs/systems/game/AGameSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/game/RTypeGameSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/input/SfmlInputSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/render/ARenderSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/render/SfmlRenderSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/network/tcpClient/ATcpClientSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/network/tcpClient/TcpClientSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/network/tcpServer/ATcpServerSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/network/tcpServer/TcpServerSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/network/udpClient/AUdpClientSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/network/udpClient/UdpClientSystem.cpp
        $ENV{ROOT_DIR}/ecs/systems/network/udpServer/AUdpServerSystem.cpp
    )
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ROOT_DIR}/build/Release)
    find_library(ECS_LIB Ecslib PATHS $ENV{ROOT_DIR}/ecs/build/)
endif ()
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
find_package(Boost COMPONENTS system serialization REQUIRED)

include_directories(Services/ GameScene/ GameScene/Enemy GameScene/Enemy/Basic GameScene/Enemy/Boss GameScene/Enemy/ScalingBoss GameScene/Enemy/Fly GameScene/Enemy/Medium GameScene/Enemy/Vessel GameScene/Enemy/ChildBoss MenuScene)

set(GAMESCENE_FILES GameScene/GameScene.cpp GameScene/PlayerBullet.cpp GameScene/Enemy/EnemyBullet.cpp GameScene/Enemy/EnemyManager.cpp GameScene/Enemy/Basic/BasicEnemy.cpp GameScene/Enemy/Fly/FlyEnemy.cpp GameScene/Enemy/Boss/BossEnemy.cpp GameScene/Enemy/Medium/MediumEnemy.cpp GameScene/Enemy/Vessel/VesselEnemy.cpp GameScene/Enemy/ScalingBoss/ScalingBossEnemy.cpp GameScene/Enemy/AEnemy.cpp GameScene/Powerup.cpp GameScene/Enemy/ChildBoss/ChildBossEnemy.cpp MenuScene/HomeMenuScene.cpp MenuScene/SettingsMenu.cpp)
set(SERVICES_FILES Services/Services.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(${BIN_NAME}
        ${GAMESCENE_FILES}
        ${SERVICES_FILES}
        ${ECS_FILES}
        Core.cpp
        main.cpp
    )
else()
    add_executable(${BIN_NAME}
        ${GAMESCENE_FILES}
        ${SERVICES_FILES}
        Core.cpp
        main.cpp
    )
    target_link_libraries(${BIN_NAME} PRIVATE ${ECS_LIB})
endif()

target_link_libraries(${BIN_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio Boost::system Boost::serialization)
set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 20)