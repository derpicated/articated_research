cmake_minimum_required(VERSION 2.6)

add_compile_options(-std=c++11) # CMake 2.8.12 or newer
#set(CMAKE_CXX_STANDARD 11) # CMake 3.1 and newer

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++")

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

# packages
find_package( OpenCV REQUIRED )

# acquisition
set(ACQUISITION_INC
    ${INCLUDE_DIR}/acquisition.hpp
)
set(ACQUISITION_SRC
    ${SRC_DIR}/acquisition.cpp
)
add_library(acquisition SHARED ${ACQUISITION_SRC} ${ACQUISITION_INC})
target_link_libraries( acquisition ${OpenCV_LIBS} )
target_include_directories ( acquisition PUBLIC ${INCLUDE_DIR} )

# vision methods
set(VISION_METHODS_INC
    ${INCLUDE_DIR}/vision_methods.hpp
)
set(VISION_METHODS_SRC
    ${SRC_DIR}/vision_methods.cpp
)
add_library( vision_methods SHARED ${VISION_METHODS_SRC} ${VISION_METHODS_INC} )
target_link_libraries( vision_methods ${OpenCV_LIBS} )
#target_include_directories ( vision_methods PUBLIC ${INCLUDE_DIR} PRIVATE ${SRC_DIR} )
target_include_directories ( vision_methods PUBLIC ${INCLUDE_DIR} )

# tests
option(TESTS "Enable Tests" OFF)

if(TESTS)
    add_subdirectory(tests)
endif(TESTS)
