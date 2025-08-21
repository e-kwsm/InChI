cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(test_util test_util_c)
set(test_strutil test_strutil_c)

set(Sources_test_util test_util.cpp)

set(Sources_test_strutil test_strutil.cpp)

add_executable(${test_util} ${Sources_test_util})
add_executable(${test_strutil} ${Sources_test_strutil})

target_link_libraries(${test_util} PUBLIC 
    gtest_main
    InChI
)
target_link_libraries(${test_strutil} PUBLIC 
    gtest_main
    InChI
)

add_test(NAME ${test_util} COMMAND ${test_util} )
add_test(NAME ${test_strutil} COMMAND ${test_strutil} )