set(ACQUISITION_INC
    ${INCLUDE_DIR}/acquisition.hpp
)
set(ACQUISITION_SRC
    ${SRC_DIR}/acquisition.cpp
)

find_package( OpenCV REQUIRED )

add_library( acquisition SHARED ${ACQUISITION_SRC} ${ACQUISITION_INC} )
target_link_libraries( acquisition ${OpenCV_LIBS} )
target_include_directories ( acquisition PUBLIC ${INCLUDE_DIR} )
