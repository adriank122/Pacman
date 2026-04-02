cmake_minimum_required(VERSION 3.10)
project(Pacman)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

option(BUILD_CLI "Build the command-line version of Pacman" ON)
option(BUILD_GUI "Build the GUI version of Pacman" ON)

# Source files for core game logic
set(CORE_SOURCES
    src/main.cpp
    src/game.cpp
    src/ghost.cpp
    src/pman.cpp
    src/map.cpp
    src/platform_utils.cpp
)

if (BUILD_CLI)
    add_executable(pacman-cli
        ${CORE_SOURCES}
        src/cli_renderer.cpp
    )
    target_include_directories(pacman-cli PRIVATE src)
    target_link_libraries(pacman-cli PRIVATE pthread)
    install(TARGETS pacman-cli RUNTIME DESTINATION bin)
endif()

if (BUILD_GUI)
    find_package(SFML 2.5 COMPONENTS graphics window system QUIET)

    if(SFML_FOUND)
        add_executable(pacman-gui 
            ${CORE_SOURCES}
            src/gui_renderer.cpp
        )
        target_include_directories(pacman-gui PRIVATE src)
        target_compile_definitions(pacman-gui PRIVATE USE_GUI=1)
        target_link_libraries(pacman-gui PRIVATE sfml-graphics sfml-window sfml-system pthread)
        
        add_custom_command(TARGET pacman-gui POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/resources
            COMMENT "Copying resources (fonts) to build directory")
        
        message(STATUS "SFML found - building GUI version")
        install(TARGETS pacman-gui RUNTIME DESTINATION bin)
    else()
        message(STATUS "SFML not found - GUI version will not be built")
        message(STATUS "Install SFML 2.5+ to build the GUI version: sudo apt-get install libsfml-dev")
    endif()
endif()

message(STATUS "Pacman build configured")
