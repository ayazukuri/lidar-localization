cmake_minimum_required (VERSION 3.18.4)
project (LIDAR)

add_executable (lidar.exe lidar.cpp icp.cpp points.cpp)
