set(VISION_METHODS_INC
    ${INCLUDE_DIR}/vision_methods.hpp
)
set(VISION_METHODS_SRC
    ${SRC_DIR}/vision_methods.cpp
)

add_library( vision_methods SHARED ${VISION_METHODS_SRC} ${VISION_METHODS_INC} )
target_link_libraries( vision_methods ${OpenCV_LIBS} )
target_include_directories ( vision_methods PUBLIC ${INCLUDE_DIR} )
