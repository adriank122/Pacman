cmake_minimum_required(VERSION 3.10)
project(Pacman)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Source files for core game logic
set(CORE_SOURCES
    src/main.cpp
    src/game.cpp
    src/ghost.cpp
    src/pman.cpp
    src/map.cpp
    src/platform_utils.cpp
    src/cli_renderer.cpp
)

add_executable(pacman-cli ${CORE_SOURCES})
target_include_directories(pacman-cli PRIVATE src)

# Link with pthread for terminal utilities
target_link_libraries(pacman-cli PRIVATE pthread)

# Installation
install(TARGETS pacman-cli
    RUNTIME DESTINATION bin
)

message(STATUS "Pacman CLI build configured")
