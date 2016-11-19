cmake_minimum_required(VERSION 3.6)
project(02_add_mouse_events)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where to find CMake modules and OpenCV
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV 3.0.1 REQUIRED core highgui imgproc)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(02_add_mouse_events main.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(02_add_mouse_events ${OpenCV_LIBS})

