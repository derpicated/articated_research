cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -O0")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}" CACHE PATH "Output directory for applications")

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SAMPLES_DIR ${CMAKE_SOURCE_DIR}/tests/samples)

include_directories(${INCLUDE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(opencv)
include(acquisition)
include(vision_methods)
include(augmentation_widget)
include(articated_app)

# tests
option(TESTS "Enable ARticated tests" OFF)

if(TESTS)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure)
    add_subdirectory(googletest)
    include_directories(SYSTEM ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    enable_testing()
    add_subdirectory(tests)
endif(TESTS)
