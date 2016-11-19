cmake_minimum_required(VERSION 3.6)
project(read_write_images)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where to find CMake modules and OpenCV
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV 2.4.13 REQUIRED core highgui imgproc)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(read_write_images main.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(read_write_images ${OpenCV_LIBS})

