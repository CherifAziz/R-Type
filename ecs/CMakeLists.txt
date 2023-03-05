cmake_minimum_required(VERSION 3.17)

project(mylib LANGUAGES CXX)

set(LIB_NAME Ecslib)

find_package(SFML COMPONENTS system window graphics audio REQUIRED)
find_package(Boost COMPONENTS system serialization REQUIRED)

add_library(${LIB_NAME} SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/components/container/ComponentManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/content/Action.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/content/Animation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/content/Movement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/content/Sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entity/EntityManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/game/AGameSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/game/RTypeGameSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/input/SfmlInputSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/render/ARenderSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/render/SfmlRenderSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/tcpClient/ATcpClientSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/tcpClient/TcpClientSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/tcpServer/ATcpServerSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/tcpServer/TcpServerSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/udpClient/AUdpClientSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/udpClient/UdpClientSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/udpServer/AUdpServerSystem.cpp
    
)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/components
    ${CMAKE_CURRENT_SOURCE_DIR}/components/container
    ${CMAKE_CURRENT_SOURCE_DIR}/components/content
    ${CMAKE_CURRENT_SOURCE_DIR}/systems
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/game
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/input
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/render
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/services
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/tcpClient
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/tcpServer
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/udpClient
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/udpServer
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/network/serialize
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/entity
    ${CMAKE_CURRENT_SOURCE_DIR}/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/storage
    ${CMAKE_CURRENT_SOURCE_DIR}/../Client/GameScene
    ${CMAKE_CURRENT_SOURCE_DIR}/../Client/GameScene/Enemy
)


target_link_libraries(${LIB_NAME} PUBLIC sfml-system sfml-window sfml-graphics sfml-audio Boost::system Boost::serialization)

# install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../build/Release/)