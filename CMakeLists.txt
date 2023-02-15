# # set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# # set(VCPKG_ROOT $(CMAKE_CURRENT_SOURCE_DIR)/vcpkg)
# # include("${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# # list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

project(rtype LANGUAGES CXX)

set(ENV{ROOT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set(CLIENT ${CMAKE_CURRENT_SOURCE_DIR}/Client)
set(SERVER ${CMAKE_CURRENT_SOURCE_DIR}/Server)

include_directories($ENV{ROOT_DIR}/ecs/ $ENV{ROOT_DIR}/ecs/components/container/ $ENV{ROOT_DIR}/ecs/components/content/ $ENV{ROOT_DIR}/ecs/entity $ENV{ROOT_DIR}/ecs/scene/ $ENV{ROOT_DIR}/ecs/systems/ $ENV{ROOT_DIR}/ecs/systems/render/ $ENV{ROOT_DIR}/ecs/systems/input/ $ENV{ROOT_DIR}/ecs/systems/storage/ $ENV{ROOT_DIR}/ecs/systems/tcpClient/ $ENV{ROOT_DIR}/ecs/systems/tcpServer/)

add_subdirectory(${CLIENT}/)
add_subdirectory(${SERVER}/)