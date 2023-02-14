cmake_minimum_required(VERSION 3.17)
project(rtype LANGUAGES CXX)
set(BIN_NAME rtype)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories($ENV{ROOT_DIR}/ecs/ $ENV{ROOT_DIR}/ecs/components/container/ $ENV{ROOT_DIR}/ecs/components/content/ $ENV{ROOT_DIR}/ecs/entity $ENV{ROOT_DIR}/ecs/scene/ $ENV{ROOT_DIR}/ecs/systems/ $ENV{ROOT_DIR}/ecs/systems/render/ $ENV{ROOT_DIR}/ecs/systems/input/ $ENV{ROOT_DIR}/ecs/systems/storage/)
# add_definitions(-Wall -Wextra -std=c++20)
# add_definitions(-Wall -WX -Wextra -std=c++20)
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

set(CPACK_PACKAGE_NAME "rtype")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_PACKAGE_FILE_NAME "rtype-${CPACK_PACKAGE_VERSION}")
set(CPACK_PACKAGE_SOURCE_FILE_NAME "rtype-source-${CPACK_PACKAGE_VERSION}")
install(TARGETS ${BIN_NAME} RUNTIME DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION .)
include(CPack)