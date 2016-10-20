set(ACQUISITION_INC
    ${INCLUDE_DIR}/acquisition.hpp
)
set(ACQUISITION_SRC
    ${SRC_DIR}/acquisition.cpp
)

add_library( acquisition SHARED ${ACQUISITION_SRC} ${ACQUISITION_INC} )
target_link_libraries( acquisition ${OpenCV_LIBS} )
target_include_directories ( acquisition PUBLIC ${INCLUDE_DIR} )

target_compile_options(acquisition PRIVATE -std=c++11 -Wall -Wextra)
