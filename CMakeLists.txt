cmake_minimum_required (VERSION 3.18.4)
project (LIDAR)

include_directories (${CMAKE_SOURCE_DIR})

add_executable (lidar.exe lidar.cpp points.cpp shape.cpp)
