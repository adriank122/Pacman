add_executable(pacman-tests
    core/config/config_test.cpp
    core/entities/ghost_test.cpp
    core/entities/pman_test.cpp
)

target_link_libraries(pacman-tests
    PRIVATE
    pacman-core
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(pacman-tests)
