cmake_minimum_required(VERSION 2.6)

add_compile_options(-std=c++11) # CMake 2.8.12 or newer
#set(CMAKE_CXX_STANDARD 11) # CMake 3.1 and newer

add_compile_options(-Wall -Wextra -Weffc++)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SAMPLES_DIR ${CMAKE_SOURCE_DIR}/tests/samples)

include_directories(${INCLUDE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(acquisition)
include(vision_methods)

# tests
option(TESTS "Enable ARticated tests" OFF)

if(TESTS)
    add_subdirectory(googletest)
    include_directories(SYSTEM ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    enable_testing()
    add_subdirectory(tests)
endif(TESTS)
