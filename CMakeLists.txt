cmake_minimum_required(VERSION 3.10)
project(Pacman)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

option(BUILD_CLI "Build the command-line version of Pacman" ON)
option(BUILD_GUI "Build the GUI version of Pacman" ON)

# Core library sources
set(CORE_SOURCES
    src/core/collision.cpp
    src/core/config.cpp
    src/core/game.cpp
    src/core/game_state.cpp
    src/core/game_timer.cpp
    src/core/ghost.cpp
    src/core/pman.cpp
    src/core/map.cpp
    src/utils/platform_utils.cpp
)

set(CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Create core library
add_library(pacman-core STATIC ${CORE_SOURCES})
target_include_directories(pacman-core PUBLIC ${CORE_INCLUDE_DIR})
target_link_libraries(pacman-core PRIVATE pthread)

# CLI executable
if (BUILD_CLI)
    add_executable(pacman-cli
        src/main.cpp
        src/rendering/cli_renderer.cpp
    )
    target_include_directories(pacman-cli PRIVATE ${CORE_INCLUDE_DIR})
    target_link_libraries(pacman-cli PRIVATE pacman-core pthread)
    add_custom_command(TARGET pacman-cli POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config.ini
        ${CMAKE_BINARY_DIR}/config.ini
        COMMENT "Copying config.ini to build directory")
    install(TARGETS pacman-cli RUNTIME DESTINATION bin)
    message(STATUS "Pacman CLI build configured")
endif()

# GUI executable
if (BUILD_GUI)
    find_package(SFML 2.5 COMPONENTS graphics window system QUIET)

    if(SFML_FOUND)
        add_executable(pacman-gui
            src/main.cpp
            src/rendering/gui_renderer.cpp
        )
        target_include_directories(pacman-gui PRIVATE ${CORE_INCLUDE_DIR})
        target_compile_definitions(pacman-gui PRIVATE USE_GUI=1)
        target_link_libraries(pacman-gui PRIVATE pacman-core sfml-graphics sfml-window sfml-system pthread)
        
        add_custom_command(TARGET pacman-gui POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/resources
            COMMENT "Copying resources (fonts) to build directory")

        add_custom_command(TARGET pacman-gui POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/config.ini
            ${CMAKE_BINARY_DIR}/config.ini
            COMMENT "Copying config.ini to build directory")
        
        message(STATUS "SFML found - building GUI version")
        install(TARGETS pacman-gui RUNTIME DESTINATION bin)
        message(STATUS "Pacman GUI build configured")
    else()
        message(STATUS "SFML not found - GUI version will not be built")
    endif()
endif()
