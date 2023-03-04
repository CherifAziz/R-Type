CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
project(rtype LANGUAGES CXX)
find_program(DPKG_EXECUTABLE dpkg)
find_program(RPM_EXECUTABLE rpm)
set(BIN_SERVER r-type_server)
set(BIN_CLIENT r-type_client)
set(ENV{ROOT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set(CLIENT ${CMAKE_CURRENT_SOURCE_DIR}/Client)
set(SERVER ${CMAKE_CURRENT_SOURCE_DIR}/Server)

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
    $ENV{ROOT_DIR}/Client/GameScene/Enemy/
    $ENV{ROOT_DIR}/Client/GameScene/Enemy/Basic/
    $ENV{ROOT_DIR}/Client/GameScene/Enemy/Fly/
    $ENV{ROOT_DIR}/Client/GameScene/Enemy/Boss/
    $ENV{ROOT_DIR}/Client/GameScene/Enemy/Medium/
    $ENV{ROOT_DIR}/Client/GameScene/Enemy/Vessel/
)

add_subdirectory(${CLIENT}/)
add_subdirectory(${SERVER}/)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(BIN_FOLDER ${CMAKE_SOURCE_DIR}/build/Release/)
    install(DIRECTORY ${BIN_FOLDER} DESTINATION .)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION .)
    set(CPACK_GENERATOR "NSIS")
else ()
    install(TARGETS ${BIN_SERVER} DESTINATION bin)
    install(TARGETS ${BIN_CLIENT} DESTINATION bin)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION bin)
    if (DPKG_EXECUTABLE)
        set(CPACK_GENERATOR "DEB")
    elseif (RPM_EXECUTABLE)
        set(CPACK_GENERATOR "RPM")
    endif ()
endif ()
set(CPACK_PACKAGE_NAME "rtype")
set(CPACK_PACKAGE_VERSION "1.0")

include(CPack)