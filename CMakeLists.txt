cmake_minimum_required(VERSION 3.7)
project(image_data_encoder)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp PNG_Img.cpp PNG_Img.h)
add_executable(image_data_encoder ${SOURCE_FILES})

find_library(ZLIB REQUIRED)
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(image_data_encoder ${PNG_LIBRARY})