CMAKE_MINIMUM_REQUIRED(VERSION 3.25)

project(rtype LANGUAGES CXX)

set(BIN_NAME r-type_server)
set(BIN_NAME_CLIENT r-type_client)

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

# set(VCPKG_ROOT $(CMAKE_CURRENT_SOURCE_DIR)/vcpkg)
# include("${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# vcpkg_install(openssl)
# find_package(OpenSSL REQUIRED)
# target_link_libraries(${BIN_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
# add_subdirectory(client/src)
# add_subdirectory(server/src)

add_executable(${BIN_NAME} server/src/test.cpp)
add_executable(${BIN_NAME_CLIENT} client/src/test_client.cpp)

# Sfml
find_package(SFML COMPONENTS system window graphics network audio CONFIG REQUIRED)
target_link_libraries(${BIN_NAME_CLIENT} PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)
# target_link_libraries(main PRIVATE sfml-main)

# OpenAL
find_package(OpenAL CONFIG REQUIRED)
target_link_libraries(${BIN_NAME_CLIENT} PRIVATE OpenAL::OpenAL)

# Boost Asio
# find_package(Boost REQUIRED [COMPONENTS <libs>...])
# target_link_libraries(main PRIVATE Boost::boost Boost::<lib1> Boost::<lib2> ...)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")