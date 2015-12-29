cmake_minimum_required(VERSION 2.8)
project(lyzp)

include_directories(${lyzp_SOURCE_DIR}/include)
link_directories(${lyzp_BINARY_DIR}/bin)

option(UnitTests "Build tests" OFF)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -W -Wall -Werror")
add_executable(lyzp ${lyzp_SOURCE_DIR}/src/lyzp.cpp)

if (UnitTests)
    set(lyzp_test_exe lyzpTests)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(${lyzp_test_exe} ${lyzp_SOURCE_DIR}/test/lyzpTests.cpp)
    target_link_libraries(${lyzp_test_exe} ${GTEST_BOTH_LIBRARIES})
endif()
