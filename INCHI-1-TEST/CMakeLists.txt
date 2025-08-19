cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(This util_test)

set(Sources
    src/unit_tests/test_util.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC 
    gtest_main
    InChI
)

add_test(
    NAME ${This} 
    COMMAND ${This}
)
