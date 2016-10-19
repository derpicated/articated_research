add_subdirectory(augmentation)
add_subdirectory(acquisition)
add_subdirectory(preprocessing)
add_subdirectory(classification)

add_compile_options(-std=c++11) # CMake 2.8.12 or newer
#set(CMAKE_CXX_STANDARD 11) # CMake 3.1 and newer
add_compile_options(-Wall -Wextra)
