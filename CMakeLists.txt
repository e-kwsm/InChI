cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(InChI C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(CTest)
include(GoogleTest)
enable_testing()

add_subdirectory(INCHI-1-SRC/INCHI_EXE/inchi-1/src)
add_subdirectory(INCHI-1-SRC/INCHI_API/libinchi/src)
add_subdirectory(INCHI-1-TEST/tests/test_unit)

