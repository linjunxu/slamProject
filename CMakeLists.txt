cmake_minimum_required(VERSION 2.8)
project( AlgoCompare )
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( AlgoCompare main.cpp )
target_link_libraries( AlgoCompare ${OpenCV_LIBS} )