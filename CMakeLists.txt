# # set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# # set(VCPKG_ROOT $(CMAKE_CURRENT_SOURCE_DIR)/vcpkg)
# # include("${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# # list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

CMAKE_MINIMUM_REQUIRED(VERSION 3.19)

project(rtype LANGUAGES CXX)

set(UDP ${CMAKE_CURRENT_SOURCE_DIR}/src/UdpServer)
set(TCP ${CMAKE_CURRENT_SOURCE_DIR}/src/TcpServer)
set(CLIENT_TCP ${CMAKE_CURRENT_SOURCE_DIR}/src/TcpClient)
set(CLIENT ${CMAKE_CURRENT_SOURCE_DIR}/src/client)
set(SERVER ${CMAKE_CURRENT_SOURCE_DIR}/src/server)

add_subdirectory(${UDP})
add_subdirectory(${TCP})
add_subdirectory(${CLIENT_TCP})
add_subdirectory(${CLIENT})
add_subdirectory(${SERVER})
