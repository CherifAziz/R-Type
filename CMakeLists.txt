CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

project(rtype LANGUAGES CXX)

set(ENV{ROOT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set(CLIENT ${CMAKE_CURRENT_SOURCE_DIR}/client)
set(SERVER ${CMAKE_CURRENT_SOURCE_DIR}/server)
set(INSTALL_SH ${CMAKE_SOURCE_DIR}/install.sh)
set(INSTALL_BAT ${CMAKE_SOURCE_DIR}/install.bat)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(BIN_FOLDER ${CMAKE_SOURCE_DIR}/build/Release)
    install(DIRECTORY ${BIN_FOLDER} DESTINATION .)
endif ()
set(CPACK_PACKAGE_NAME "rtype")
set(CPACK_PACKAGE_VERSION "1.0")

include_directories(
    $ENV{ROOT_DIR}/ecs/
    $ENV{ROOT_DIR}/ecs/components/container/
    $ENV{ROOT_DIR}/ecs/components/content/
    $ENV{ROOT_DIR}/ecs/core
    $ENV{ROOT_DIR}/ecs/entity/
    $ENV{ROOT_DIR}/ecs/scene/
    $ENV{ROOT_DIR}/ecs/storage/
    $ENV{ROOT_DIR}/ecs/systems/
    $ENV{ROOT_DIR}/ecs/systems/render/
    $ENV{ROOT_DIR}/ecs/systems/game/
    $ENV{ROOT_DIR}/ecs/systems/input/
    $ENV{ROOT_DIR}/ecs/systems/network/tcpClient/
    $ENV{ROOT_DIR}/ecs/systems/network/tcpServer/
    $ENV{ROOT_DIR}/ecs/systems/network/udpServer/
    $ENV{ROOT_DIR}/ecs/systems/network/udpClient/
    $ENV{ROOT_DIR}/ecs/systems/network/serialize/
    $ENV{ROOT_DIR}/ecs/systems/network/services/
)

add_subdirectory(${CLIENT}/)
add_subdirectory(${SERVER}/)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(TARGETS rtype DESTINATION Release)
endif ()
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION Release)
install(FILES ${INSTALL_SH} DESTINATION .)
install(FILES ${INSTALL_BAT} DESTINATION .)
include(CPack)


set(CLIENT ${CMAKE_CURRENT_SOURCE_DIR}/Client)
set(SERVER ${CMAKE_CURRENT_SOURCE_DIR}/Server)