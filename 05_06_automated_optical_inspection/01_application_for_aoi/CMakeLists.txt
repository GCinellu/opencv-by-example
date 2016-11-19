cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0012 NEW)
project(01_application_for_aoi)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where to find CMake modules and OpenCV
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV 3.1.0 REQUIRED core highgui imgproc)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(01_application_for_aoi main.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(01_application_for_aoi ${OpenCV_LIBS})

