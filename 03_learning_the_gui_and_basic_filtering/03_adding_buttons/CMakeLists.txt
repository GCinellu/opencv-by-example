cmake_minimum_required(VERSION 3.6)
project(03_adding_buttons)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where to find CMake modules and OpenCV
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV 2.4.13 REQUIRED core highgui imgproc)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(03_adding_buttons main.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(03_adding_buttons ${OpenCV_LIBS})

